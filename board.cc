#include "board.h"
#include "std.h"
#include "string-util.h"

Board::Board() {
  // Use a FEN string representing the default chess starting position.
  SetupFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}

Board::Board(const string& fen) {
  SetupFen(fen);
}

void Board::SetupFen(const string& fen) {
  vector<string> tokens = StringUtil::Split(fen);
  if (tokens.size() != 6) {
    throw "Invalid FEN string.";
  }
  const string piecePlacement = tokens[0];
  const string activeColorString = tokens[1];
  const string castleString = tokens[2];
  const string enPassantTargetString = tokens[3];
  const string halfmoveClockString = tokens[4];
  const string fullMoveNumberString = tokens[5];
  const vector<string> ranks = StringUtil::Split(piecePlacement, '/');
  if (ranks.size() != 8) {
    throw "Invalid FEN string.";
  }
  squares[0][0] = BlackRook;
}
