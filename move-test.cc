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

TEST_CASE("Algebraic move notation constructor", "[Move]") {
  Move move("e2e4");
  REQUIRE(move.from.rank == 6);
  REQUIRE(move.from.file == 4);
  REQUIRE(move.to.rank == 4);
  REQUIRE(move.to.file == 4);
}

TEST_CASE("Algebraic knight move", "[Move]") {
  Move move("g8f6");
  REQUIRE(move.from.rank == 0);
  REQUIRE(move.from.file == 6);
  REQUIRE(move.to.rank == 2);
  REQUIRE(move.to.file == 5);
}

TEST_CASE("Equality operator (Move)", "[Move]") {
  REQUIRE(Point("e4") == Point("e4"));
  REQUIRE(Point("e4") != Point("e3"));
  REQUIRE(Point("e4") != Point("d4"));
  REQUIRE(Point("b6") != Point("c7"));
  REQUIRE(Point(3, 4) == Point(3, 4));
  REQUIRE(Point(3, 4) != Point(2, 4));
  REQUIRE(Point(3, 4) != Point(3, 5));
}

TEST_CASE("MovesToStrings", "[Move]") {
  const vector<Move> moves = { Move("b1a3"), Move("g8h6") };
  const vector<string> actual = MovesToStrings(moves);
  const vector<string> expected = {"b1a3", "g8h6"};
  REQUIRE(actual == expected);
}

TEST_CASE("Move generation: opening position", "[Move]") {
  const string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  const Board b = FenToBoard(fen);
  const vector<Move> moves = GenerateLegalMoves(b);
  const vector<string> actual = MovesToStrings(moves);
  const vector<string> expected = {"b1a3", "b1c3", "g1f3", "g1h3"};
  REQUIRE(actual == expected);
}
