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
  squares[0][0] = BlackRook;
}
