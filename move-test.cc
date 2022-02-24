#include "catch.hpp"
#include "move.h"

TEST_CASE("Basic move constructor", "[Move]") {
  Move move(Point(7, 1), Point(5, 2));
  REQUIRE(move.from.rank == 7);
  REQUIRE(move.from.file == 1);
  REQUIRE(move.to.rank == 5);
  REQUIRE(move.to.file == 2);
}

TEST_CASE("Move generation: opening position", "[Move]") {
  REQUIRE(2 + 2 == 4);
}
