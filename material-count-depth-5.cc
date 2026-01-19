#include "board.h"
#include "check.h"
#include "fen.h"
#include "makemove.h"
#include "material-count.h"
#include "movegen.h"
#include "std.h"
#include "string-util.h"

// The chess board.
Board b;

void ResetBoard() {
  string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  b = FenToBoard(fen);
}

int AlphaBeta(Board& board, int depth, int alpha, int beta) {
  if (depth == 0) {
    return MaterialCount(board);
  }
  vector<Move> moves = GenerateLegalMoves(board);
  if (moves.empty()) {
    return IsSideToMoveInCheck(board) ? -1000 : 0;
  }
  for (const Move& move : moves) {
    Irreversible irr = board.irreversible;
    MakeMove(board, move);
    int score = -AlphaBeta(board, depth - 1, -beta, -alpha);
    UndoMove(board, move, irr);
    if (score >= beta) {
      return beta;
    }
    if (score > alpha) {
      alpha = score;
    }
  }
  return alpha;
}

// Command is "go". Output a randomly chosen legal move.
void Go(const string& command) {
  vector<Move> moves = GenerateLegalMoves(b);
  if (moves.empty()) {
    return;
  }
  int bestMoveIndex = -1;
  int alpha = -1000;
  int beta = -alpha;
  int depth = 5;
  for (size_t i = 0; i < moves.size(); i++) {
    Irreversible irr = b.irreversible;
    MakeMove(b, moves[i]);
    int score = -AlphaBeta(b, depth - 1, -beta, -alpha);
    UndoMove(b, moves[i], irr);
    if (score > alpha || bestMoveIndex == -1) {
      alpha = score;
      bestMoveIndex = i;
    }
  }
  if (bestMoveIndex == -1) {
    return;
  }
  Move bestMove = moves[bestMoveIndex];
  string bestMoveString = bestMove.ToString();
  cout << "bestmove " << bestMoveString << endl;
}

// Command is "isready". Answer with "readyok".
void IsReady(const string& command) {
  cout << "readyok" << endl;
}

// Command is "position". Set up a board position.
void Position(const string& command) {
  vector<string> tokens = StringUtil::Split(command);
  if (tokens[1] == "fen") {
    string fen = command.substr(13);
    b = FenToBoard(fen);
  } else if (tokens[1] == "startpos") {
    ResetBoard();
    if (tokens[2] == "moves") {
      for (size_t i = 3; i < tokens.size(); i++) {
        string chessMoveInUciNotation = tokens[i];
        vector<Move> moves = GenerateLegalMoves(b);
        bool isLegalMove = false;
        for (const Move& m : moves) {
          if (m.ToString() == chessMoveInUciNotation) {
            isLegalMove = true;
            MakeMove(b, m);
            break;
          }
        }
        if (!isLegalMove) {
          // Illegal move found in the moves list. Stop processing further moves. Reset the board.
          ResetBoard();
          break;
        }
      }
    }
  } else {
    // Unknown type of position command. Reset the board and hope for the best.
    ResetBoard();
  }
}

// Command is "quit". Exit the program.
void Quit(const string& command) {
  exit(0);
}

// Command is "uci". Print basic info about this chess engine.
void Uci(const string& command) {
  cout << "id name randombot" << endl;
  cout << "id author jeff" << endl;
  cout << "uciok" << endl;
}

// Command is "ucinewgame". Reset the board. No stdout output required.
void UciNewGame(const string& command) {
  ResetBoard();
}

// UCI commands are registered in this map.
typedef void (*UciCommand)(const string& command);
map<string, UciCommand> commands;

void Dispatch(const string& line) {
    vector<string> tokens = StringUtil::Split(line);
    if (tokens.size() == 0) {
      return;
    }
    const string command = tokens[0];
    if (commands.count(command) == 0) {
      // Unknown command. As per the UCI protocol, ignore it.
      return;
    }
    const UciCommand handler = commands[command];
    handler(line);
}

int main(int argc, char **argv) {
  ResetBoard();
  // Register UCI commands.
  commands["exit"] = Quit;
  commands["go"] = Go;
  commands["isready"] = IsReady;
  commands["position"] = Position;
  commands["quit"] = Quit;
  commands["uci"] = Uci;
  commands["ucinewgame"] = UciNewGame;
  // Process the input line-by-line.
  string line;
  while (getline(cin, line)) {
    Dispatch(line);
  }
  return 0;
}
