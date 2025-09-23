#include "board.h"
#include "fen.h"
#include "std.h"
#include "test.h"

TEST(CopyBoard) {
  string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  Board b = FenToBoard(fen);
  Board c = b;
  ASSERT(c == b);
  c.color[2][1] = White;
  ASSERT(c != b);
}
