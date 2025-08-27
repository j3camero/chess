#include "board.h"
#include "fen.h"
#include "perft.h"
#include "std.h"
#include "test.h"

TEST(PerftWithZeroDepth) {
  string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  Board b = FenToBoard(fen);
  int depth = 0;
  uint64_t p = Perft(b, depth);
  ASSERT(p == 1);
  // Board original = FenToBoard(fen);
  // ASSERT(b == original);
}

TEST(PerftWithDepth1) {
  string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  Board b = FenToBoard(fen);
  int depth = 1;
  uint64_t p = Perft(b, depth);
  ASSERT(p == 20);
  // Board original = FenToBoard(fen);
  // ASSERT(b == original);
}

TEST(PerftWithDepth2) {
  string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  Board b = FenToBoard(fen);
  int depth = 2;
  uint64_t p = Perft(b, depth);
  ASSERT(p == 400);
  // Board original = FenToBoard(fen);
  // ASSERT(b == original);
}

TEST(PerftWithDepth3) {
  string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  Board b = FenToBoard(fen);
  int depth = 3;
  uint64_t p = Perft(b, depth);
  ASSERT(p == 8902);
  // Board original = FenToBoard(fen);
  // ASSERT(b == original);
}

TEST(PerftWithDepth4) {
  // TODO: this test fails!
  string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  Board b = FenToBoard(fen);
  int depth = 4;
  uint64_t p = Perft(b, depth);
  ASSERT(p == 197281);
  // Board original = FenToBoard(fen);
  // ASSERT(b == original);
}

TEST(PerftWithManyDifferentDepths) {
  string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  Board b = FenToBoard(fen);
  for (int d = 0; d <= 5; d++) {
    int p = Perft(b, d);
    cout << "perft(" << d << ") = " << p << endl;
  }
}
