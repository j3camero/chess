#include "board.h"
#include "catch.hpp"
#include "fen.h"
#include "move.h"
#include "std.h"

TEST_CASE("Basic move constructor", "[Move]") {
  Move move(Point(7, 1), Point(5, 2));
  REQUIRE(move.from.rank == 7);
  REQUIRE(move.from.file == 1);
  REQUIRE(move.to.rank == 5);
  REQUIRE(move.to.file == 2);
}

TEST_CASE("Move generation: opening position", "[Move]") {
  const string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  Board b = FenToBoard(fen);
  vector<Move> moves = GenerateLegalMoves(b);
  REQUIRE(moves.size() == 4);
}
