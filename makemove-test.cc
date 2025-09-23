#include "board.h"
#include "fen.h"
#include "makemove.h"
#include "move.h"
#include "test.h"

TEST(MakeMoveTestPlaceholder) {
  // TODO: make unit tests. For now the plan is to rely on perft.
  ASSERT(true);
}

TEST(MakeMoveA2A3A7A5H2H3) {
  string fen = "rnbqkbnr/1ppppppp/8/p7/8/P7/1PPPPPPP/RNBQKBNR w KQkq - 0 2";
  Board b = FenToBoard(fen);
  Irreversible i = b.irreversible;
  Move m("h2h3");
  MakeMove(b, m);
  string exp = "rnbqkbnr/1ppppppp/8/p7/8/P6P/1PPPPPP1/RNBQKBNR b KQkq - 0 2";
  Board expected = FenToBoard(exp);
  ASSERT(b == expected);
  UndoMove(b, m, i);
  Board original = FenToBoard(fen);
  ASSERT(b == original);
}

TEST(MakeMoveA2A3A7A5B2B4) {
  string fen = "rnbqkbnr/1ppppppp/8/p7/8/P7/1PPPPPPP/RNBQKBNR w KQkq - 0 2";
  Board b = FenToBoard(fen);
  Irreversible i = b.irreversible;
  Move m("b2b4");
  MakeMove(b, m);
  string exp = "rnbqkbnr/1ppppppp/8/p7/1P6/P7/2PPPPPP/RNBQKBNR b KQkq b3 0 2";
  Board expected = FenToBoard(exp);
  ASSERT(b == expected);
  UndoMove(b, m, i);
  Board original = FenToBoard(fen);
  ASSERT(b == original);
}

TEST(MakeMoveA2A3A7A5B2B4A5B4) {
  string fen = "rnbqkbnr/1ppppppp/8/p7/1P6/P7/2PPPPPP/RNBQKBNR b KQkq b3 0 2";
  Board b = FenToBoard(fen);
  Irreversible i = b.irreversible;
  Move m("a5b4", true, Pawn);
  MakeMove(b, m);
  string exp = "rnbqkbnr/1ppppppp/8/8/1p6/P7/2PPPPPP/RNBQKBNR w KQkq - 0 3";
  Board expected = FenToBoard(exp);
  ASSERT(b == expected);
  UndoMove(b, m, i);
  Board original = FenToBoard(fen);
  ASSERT(b == original);
}

TEST(MakeMoveA2A4B8C6A4A5B7B5) {
  string fen = "r1bqkbnr/p1pppppp/2n5/Pp6/8/8/1PPPPPPP/RNBQKBNR w KQkq b6 0 3";
  Board b = FenToBoard(fen);
  Irreversible i = b.irreversible;
  Move m("a5b6", true, Pawn);
  MakeMove(b, m);
  string exp = "r1bqkbnr/p1pppppp/1Pn5/8/8/8/1PPPPPPP/RNBQKBNR b KQkq - 0 3";
  Board expected = FenToBoard(exp);
  ASSERT(b == expected);
  UndoMove(b, m, i);
  Board original = FenToBoard(fen);
  ASSERT(b == original);
}
