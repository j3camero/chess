const { Chess } = require('chess.js')
const fs = require('fs');
const readline = require('readline');
const { decompressStream } = require('@skhaz/zstd'); // or require('zstd-napi') and use its decompression method

const filePath = 'lichess_db_eval.jsonl.zst';

const numer = {};
const denom = {};
const moveCsv = {};

function TallyOneChessPosition(fen, bestMoveUci) {
  const chessPosition = new Chess(fen);
  const legalMoves = chessPosition.moves({ verbose: true });
  for (const move of legalMoves) {
    const uciMoveNotation = move.from + move.to + (move.promotion || '');
    const allFields = [move.color,
                       move.piece,
                       move.from,
                       move.to,
                       move.captured || '',
                       move.promotion || ''];
    const moveKey = allFields.join('');
    moveCsv[moveKey] = allFields.join(',');
    denom[moveKey] = (denom[moveKey] || 0) + 1;
    if (uciMoveNotation === bestMoveUci) {
      numer[moveKey] = (numer[moveKey] || 0) + 1;
    }
  }
}

function CalculateConditionalProbabilitiesForAllMoves() {
  const writeStream = fs.createWriteStream('moveprob.csv', { flags: 'w' });
  writeStream.write('color,piece,from,to,capture,promotion,count,best,prob\n');
  for (const moveKey in denom) {
    const d = denom[moveKey];
    const n = numer[moveKey] || 0;
    const p = n / d;
    let csvLine = moveCsv[moveKey];
    csvLine += ',' + d + ',' + n + ',' + p + '\n';
    writeStream.write(csvLine);
  }
  writeStream.end();
}

// Create a readable stream from the compressed file
const fileStream = fs.createReadStream(filePath);

// Pipe the file stream through the Zstd decompress stream
const decompressedStream = fileStream.pipe(decompressStream());

// Create a readline interface to process the decompressed stream line by line
const rl = readline.createInterface({
  input: decompressedStream,
  crlfDelay: Infinity // Handle both Windows (\r\n) and Unix (\n) line endings correctly
});

const startTime = Date.now();
let lineCount = 0;

// Listen for the 'line' event
rl.on('line', (line) => {
  const chessPosition = JSON.parse(line);
  const fen = chessPosition.fen;
  let bestMove = 'NONE';
  let maxDepth = -1;
  for (const eval of chessPosition.evals) {
    if (eval.depth > maxDepth) {
      maxDepth = eval.depth;
      const pv = eval.pvs[0].line;
      const moves = pv.split(' ');
      bestMove = moves[0];
    }
  }
  TallyOneChessPosition(fen, bestMove);
  lineCount++;
  if (lineCount % 10000 === 0) {
    CalculateConditionalProbabilitiesForAllMoves();
    const currentTime = Date.now();
    const elapsedTime = currentTime - startTime;
    const goal = 354637151;
    const progress = lineCount / goal;
    const estimatedRuntime = elapsedTime * goal / lineCount;
    const estimatedFinish = startTime + estimatedRuntime;
    const eta = new Date(estimatedFinish);
    console.log(lineCount, '/', goal, 'ETA', eta.toISOString());
  }
});

// Listen for the 'end' event when finished reading all lines
rl.on('end', () => {
  console.log(`Finished reading ${lineCount} lines.`);
  CalculateConditionalProbabilitiesForAllMoves();
});

// Handle potential errors
fileStream.on('error', (err) => {
  console.error('Error reading file stream:', err);
});

decompressedStream.on('error', (err) => {
  console.error('Error during decompression:', err);
});

rl.on('error', (err) => {
  console.error('Error in readline interface:', err);
});
