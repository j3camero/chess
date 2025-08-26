#include "board.h"
#include "fen.h"
#include "perft.h"
#include "test.h"

TEST(PerftWithZeroDepth) {
  string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  Board b = FenToBoard(fen);
  int depth = 0;
  int p = Perft(b, depth);
  ASSERT(p == 1);
}
