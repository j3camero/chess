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

TEST(PerftKiwipete) {
  string fen = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1";
  Board b = FenToBoard(fen);
  ASSERT(Perft(b, 0) == 1);
  ASSERT(Perft(b, 1) == 48);
  ASSERT(Perft(b, 2) == 2039);
  ASSERT(Perft(b, 3) == 97862);
  //ASSERT(Perft(b, 4) == 4085603);
  //ASSERT(Perft(b, 5) == 193690690);
  //ASSERT(Perft(b, 6) == 8031647685);
  Board original = FenToBoard(fen);
  ASSERT(b == original);
}

TEST(PerftKiwipeteC3B1) {
  string fen = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/5Q1p/PPPBBPPP/RN2K2R b KQkq - 1 1";
  Board b = FenToBoard(fen);
  ASSERT(Perft(b, 0) == 1);
  ASSERT(Perft(b, 1) == 42);
  ASSERT(Perft(b, 2) == 2038);
  Board original = FenToBoard(fen);
  ASSERT(b == original);
}

TEST(PerftKiwipeteC3B1A6B5) {
  string fen = "r3k2r/p1ppqpb1/1n2pnp1/1b1PN3/1p2P3/5Q1p/PPPBBPPP/RN2K2R w KQkq - 2 2";
  Board b = FenToBoard(fen);
  ASSERT(Perft(b, 0) == 1);
  ASSERT(Perft(b, 1) == 48);
  Board original = FenToBoard(fen);
  ASSERT(b == original);
}

TEST(PerftPosition3) {
  string fen = "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1";
  Board b = FenToBoard(fen);
  ASSERT(Perft(b, 0) == 1);
  ASSERT(Perft(b, 1) == 14);
  ASSERT(Perft(b, 2) == 191);
  //ASSERT(Perft(b, 3) == 1812);
  //ASSERT(Perft(b, 4) == 43238);
  //ASSERT(Perft(b, 5) == 193690690);
  //ASSERT(Perft(b, 6) == 8031647685);
  Board original = FenToBoard(fen);
  ASSERT(b == original);
}

TEST(PerftWithMemory) {
  string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  Board b = FenToBoard(fen);
  ASSERT(PerftWithMemory(b, 0) == 1);
  ASSERT(PerftWithMemory(b, 1) == 20);
  ASSERT(PerftWithMemory(b, 2) == 400);
  ASSERT(PerftWithMemory(b, 3) == 8902);
  ASSERT(PerftWithMemory(b, 4) == 197281);
  // ASSERT(PerftWithMemory(b, 5) == 4865609);
  // ASSERT(PerftWithMemory(b, 6) == 119060324);
  // ASSERT(PerftWithMemory(b, 7) == 3195901860);
  Board original = FenToBoard(fen);
  ASSERT(b == original);
}

TEST(FindUndoMoveBugsOpeningPosition) {
  string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  Board b = FenToBoard(fen);
  bool foundBugs = FindUndoMoveInconsistencies(b, 3);
  ASSERT(!foundBugs);
}

TEST(FindUndoMoveBugsKiwipete) {
  string fen = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1";
  Board b = FenToBoard(fen);
  bool foundBugs = FindUndoMoveInconsistencies(b, 3);
  ASSERT(!foundBugs);
}
