const { Chess } = require('chess.js')
const fs = require('fs');
const readline = require('readline');
const { decompressStream } = require('@skhaz/zstd'); // or require('zstd-napi') and use its decompression method

const filePath = 'lichess_db_eval.jsonl.zst';
const skipHowManyFirstLines = 0;

const numer = {};
const denom = {};
const moveCsv = {};
let impossibleCastlingRightsPositionCount = 0;

function TallyOneChessPosition(fen, bestMoveUci) {
  let chessPosition;
  try {
    chessPosition = new Chess(fen);
  } catch (error) {
    console.log('Error parsing chess position');
    console.log('FEN:', fen);
    console.log('ERROR:', error);
    return;
  }
  if (PositionHasImpossibleCastlingRights(chessPosition)) {
    impossibleCastlingRightsPositionCount++;
    return;
  }
  const legalMoves = chessPosition.moves({ verbose: true });
  let foundMatchingBestMove = false;
  for (const move of legalMoves) {
    const uciMoveNotation = move.from + move.to + (move.promotion || '');
    let isCastleMove = '';
    if (move.isKingsideCastle()) {
      isCastleMove = 'CASTLE';
      const alternateKingCastleStrings = ['e8h8', 'e1h1', '0-0', 'O-O'];
      if (alternateKingCastleStrings.includes(bestMoveUci)) {
        bestMoveUci = uciMoveNotation;
      }
    }
    if (move.isQueensideCastle()) {
      isCastleMove = 'CASTLE';
      const alternateKingCastleStrings = ['e8a8', 'e1a1', '0-0-0', 'O-O-O'];
      if (alternateKingCastleStrings.includes(bestMoveUci)) {
        bestMoveUci = uciMoveNotation;
      }
    }
    const allFields = [move.color,
                       move.piece,
                       move.from,
                       move.to,
                       move.captured || '',
                       move.promotion || '',
                       move.isEnPassant() ? 'EP' : '',
                       isCastleMove];
    const moveKey = allFields.join('');
    moveCsv[moveKey] = allFields.join(',');
    denom[moveKey] = (denom[moveKey] || 0) + 1;
    if (uciMoveNotation === bestMoveUci) {
      numer[moveKey] = (numer[moveKey] || 0) + 1;
      foundMatchingBestMove = true;
    }
  }
  if (!foundMatchingBestMove) {
    console.log('WARNING: no matching best move');
    console.log('FEN:', fen);
    console.log('bestMoveUci:', bestMoveUci);
    throw 'No matching best move';
  }
}

function CalculateConditionalProbabilitiesForAllMoves(filenameSuffix) {
  const writeStream = fs.createWriteStream(`moveprob-${filenameSuffix}.csv`, { flags: 'w' });
  writeStream.write('color,piece,from,to,capture,promotion,castle,count,best,prob\n');
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

// Detects weird Chess960 positions and other impossible positions.
function PositionHasImpossibleCastlingRights(chessPosition) {
  const turn = chessPosition.turn();
  const rights = chessPosition.getCastlingRights(turn);
  if (!('k' in rights)) {
    throw 'King castle rights missing.';
  }
  if (!('q' in rights)) {
    throw 'Queen castle rights missing.';
  }
  if (rights['k']) {
    if (turn === 'w') {
      const e1 = chessPosition.get('e1');
      if (!e1 || e1.color !== 'w' || e1.type !== 'k') {
        return true;
      }
      const h1 = chessPosition.get('h1');
      if (!h1 || h1.color !== 'w' || h1.type !== 'r') {
        return true;
      }
    } else if (turn === 'b') {
      const e8 = chessPosition.get('e8');
      if (!e8 || e8.color !== 'b' || e8.type !== 'k') {
        return true;
      }
      const h8 = chessPosition.get('h8');
      if (!h8 || h8.color !== 'b' || h8.type !== 'r') {
        return true;
      }
    }
  }
  if (rights['q']) {
    if (turn === 'w') {
      const e1 = chessPosition.get('e1');
      if (!e1 || e1.color !== 'w' || e1.type !== 'k') {
        return true;
      }
      const a1 = chessPosition.get('a1');
      if (!a1 || a1.color !== 'w' || a1.type !== 'r') {
        return true;
      }
    } else if (turn === 'b') {
      const e8 = chessPosition.get('e8');
      if (!e8 || e8.color !== 'b' || e8.type !== 'k') {
        return true;
      }
      const a8 = chessPosition.get('a8');
      if (!a8 || a8.color !== 'b' || a8.type !== 'r') {
        return true;
      }
    }
  }
  return false;
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
  lineCount++;
  if (lineCount < skipHowManyFirstLines) {
    return;
  }
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
  if (lineCount % 10000 === 0) {
    const currentTime = Date.now();
    const elapsedTime = currentTime - startTime;
    const goal = 354637151;
    const progress = lineCount / goal;
    const percent = 100 * progress;
    const formattedPercent = percent.toFixed(2) + '%';
    const estimatedRuntime = elapsedTime * goal / lineCount;
    const estimatedFinish = startTime + estimatedRuntime;
    const eta = new Date(estimatedFinish);
    console.log(lineCount, '/', goal, formattedPercent,
                'ETA', eta.toISOString(),
                'skipcount', impossibleCastlingRightsPositionCount);
  }
  if (lineCount % 100000 === 0) {
    CalculateConditionalProbabilitiesForAllMoves(lineCount);
    console.log('Saved progress to file');
  }
});

// Listen for the 'end' event when finished reading all lines
rl.on('end', () => {
  console.log(`Finished reading ${lineCount} lines.`);
  CalculateConditionalProbabilitiesForAllMoves('final');
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
