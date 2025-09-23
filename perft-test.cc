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
  Board original = FenToBoard(fen);
  ASSERT(b == original);
}

TEST(PerftWithDepth1) {
  string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  Board b = FenToBoard(fen);
  int depth = 1;
  uint64_t p = Perft(b, depth);
  ASSERT(p == 20);
  Board original = FenToBoard(fen);
  ASSERT(b == original);
}

TEST(PerftWithDepth2) {
  string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  Board b = FenToBoard(fen);
  int depth = 2;
  uint64_t p = Perft(b, depth);
  ASSERT(p == 400);
  Board original = FenToBoard(fen);
  ASSERT(b == original);
}

TEST(PerftWithDepth3) {
  string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  Board b = FenToBoard(fen);
  int depth = 3;
  uint64_t p = Perft(b, depth);
  ASSERT(p == 8902);
  Board original = FenToBoard(fen);
  ASSERT(b == original);
}

TEST(PerftWithDepth4) {
  string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  Board b = FenToBoard(fen);
  int depth = 4;
  uint64_t p = Perft(b, depth);
  ASSERT(p == 197281);
  Board original = FenToBoard(fen);
  ASSERT(b == original);
}

// This test takes too long to run so it has been disabled. Uncomment if needed
// for debugging. The plan is to make a memory-assisted perft to check these
// higher perft numbers more efficiently.
// TEST(PerftWithDepth5) {
//   string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
//   Board b = FenToBoard(fen);
//   int depth = 5;
//   uint64_t p = Perft(b, depth);
//   ASSERT(p == 4865609);
//   Board original = FenToBoard(fen);
//   ASSERT(b == original);
// }

TEST(PerftA2A3) {
  string fen = "rnbqkbnr/pppppppp/8/8/8/P7/1PPPPPPP/RNBQKBNR b KQkq - 0 1";
  Board b = FenToBoard(fen);
  int depth = 3;
  uint64_t p = Perft(b, depth);
  Board original = FenToBoard(fen);
  ASSERT(b == original);
  ASSERT(p == 8457);
}

TEST(PerftA2A3A7A5) {
  string fen = "rnbqkbnr/1ppppppp/8/p7/8/P7/1PPPPPPP/RNBQKBNR w KQkq - 0 2";
  Board b = FenToBoard(fen);
  int depth = 2;
  uint64_t p = Perft(b, depth);
  ASSERT(p == 399);
  Board original = FenToBoard(fen);
  ASSERT(b == original);
}

TEST(PerftA2A3A7A5H2H3) {
  string fen = "rnbqkbnr/1ppppppp/8/p7/8/P6P/1PPPPPP1/RNBQKBNR b KQkq - 0 2";
  Board b = FenToBoard(fen);
  int depth = 1;
  uint64_t p = Perft(b, depth);
  ASSERT(p == 21);
  Board original = FenToBoard(fen);
  ASSERT(b == original);
}

TEST(PerftA2A4) {
  string fen = "rnbqkbnr/pppppppp/8/8/P7/8/1PPPPPPP/RNBQKBNR b KQkq - 0 1";
  Board b = FenToBoard(fen);
  int depth = 4;
  uint64_t p = Perft(b, depth);
  ASSERT(p == 217832);
  Board original = FenToBoard(fen);
  ASSERT(b == original);
}

TEST(PerftA2A4B8C6) {
  string fen = "r1bqkbnr/pppppppp/2n5/8/P7/8/1PPPPPPP/RNBQKBNR w KQkq - 0 2";
  Board b = FenToBoard(fen);
  int depth = 3;
  uint64_t p = Perft(b, depth);
  ASSERT(p == 10746);
  Board original = FenToBoard(fen);
  ASSERT(b == original);
}

TEST(PerftA2A4B8C6A4A5) {
  string fen = "r1bqkbnr/pppppppp/2n5/P7/8/8/1PPPPPPP/RNBQKBNR b KQkq - 0 2";
  Board b = FenToBoard(fen);
  int depth = 2;
  uint64_t p = Perft(b, depth);
  ASSERT(p == 461);
  Board original = FenToBoard(fen);
  ASSERT(b == original);
}

TEST(PerftA2A4B8C6A4A5B7B5) {
  string fen = "r1bqkbnr/p1pppppp/2n5/Pp6/8/8/1PPPPPPP/RNBQKBNR w KQkq b6 0 3";
  Board b = FenToBoard(fen);
  int depth = 1;
  uint64_t p = Perft(b, depth);
  ASSERT(p == 23);
  Board original = FenToBoard(fen);
  ASSERT(b == original);
}

TEST(PerftA2A4B8C6B2B4) {
  string fen = "r1bqkbnr/pppppppp/2n5/8/PP6/8/2PPPPPP/RNBQKBNR b KQkq b3 0 2";
  Board b = FenToBoard(fen);
  int depth = 2;
  uint64_t p = Perft(b, depth);
  ASSERT(p == 482);
  Board original = FenToBoard(fen);
  ASSERT(b == original);
}

TEST(PerftA2A4B8C6B2B4A7A5) {
  string fen = "r1bqkbnr/1ppppppp/2n5/p7/PP6/8/2PPPPPP/RNBQKBNR w KQkq a6 0 3";
  Board b = FenToBoard(fen);
  int depth = 1;
  uint64_t p = Perft(b, depth);
  ASSERT(p == 22);
  Board original = FenToBoard(fen);
  ASSERT(b == original);
}
