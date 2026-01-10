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
  ASSERT(Perft(b, 3) == 2812);
  ASSERT(Perft(b, 4) == 43238);
  ASSERT(Perft(b, 5) == 674624);
  //ASSERT(Perft(b, 6) == 11030083);
  //ASSERT(Perft(b, 7) == 178633661);
  //ASSERT(Perft(b, 8) == 3009794393);
  Board original = FenToBoard(fen);
  ASSERT(b == original);
}

TEST(PerftPosition4) {
  string fen = "r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1";
  Board b = FenToBoard(fen);
  ASSERT(Perft(b, 0) == 1);
  ASSERT(Perft(b, 1) == 6);
  ASSERT(Perft(b, 2) == 264);
  ASSERT(Perft(b, 3) == 9467);
  ASSERT(Perft(b, 4) == 422333);
  //ASSERT(Perft(b, 5) == 15833292);
  //ASSERT(Perft(b, 6) == 706045033);
  Board original = FenToBoard(fen);
  ASSERT(b == original);
}

TEST(PerftPosition5) {
  string fen = "rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8";
  Board b = FenToBoard(fen);
  ASSERT(Perft(b, 0) == 1);
  ASSERT(Perft(b, 1) == 44);
  ASSERT(Perft(b, 2) == 1486);
  ASSERT(Perft(b, 3) == 62379);
  ASSERT(Perft(b, 4) == 2103487);
  //ASSERT(Perft(b, 5) == 89941194);
  Board original = FenToBoard(fen);
  ASSERT(b == original);
}

TEST(PerftPosition6) {
  string fen = "r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10";
  Board b = FenToBoard(fen);
  ASSERT(Perft(b, 0) == 1);
  ASSERT(Perft(b, 1) == 46);
  ASSERT(Perft(b, 2) == 2079);
  ASSERT(Perft(b, 3) == 89890);
  ASSERT(Perft(b, 4) == 3894594);
  //ASSERT(Perft(b, 5) == 164075551);
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

TEST(PerftPosition7) {
  //string fen = "rn2kbnr/p1q1ppp1/1ppp3p/8/4B1b1/2P4P/PPQPPP2/RNB1K1NR w KQkq - 0 1";
  //Board b = FenToBoard(fen);
  //bool foundBugs = FindUndoMoveInconsistencies(b, 6);
  //ASSERT(!foundBugs);
  //ASSERT(Perft(b, 6) == 622445426);
}
