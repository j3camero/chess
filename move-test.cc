#include "catch.hpp"
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
  REQUIRE(Move("e2e4") == Move("e2e4"));
  REQUIRE(Move("e2e4") != Move("e2e3"));
  REQUIRE(Move("e2e4") != Move("d4e4"));
  REQUIRE(Move("a3b6") != Move("c7a1"));
  REQUIRE(Move("h6f7") == Move(Point(2, 7), Point(1, 5)));
}

TEST_CASE("MovesToStrings", "[Move]") {
  const vector<Move> moves = { Move("b1a3"), Move("g8h6") };
  const vector<string> actual = MovesToStrings(moves);
  const vector<string> expected = { "b1a3", "g8h6" };
  REQUIRE(actual == expected);
}
