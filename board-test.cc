#include "catch.hpp"
#include "board.h"

TEST_CASE("Default constructor", "[Board]") {
  Board b;
  REQUIRE(b.squares[0][0] == Board::BlackRook);
}
