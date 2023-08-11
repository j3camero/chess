#include "catch.hpp"
#include "color.h"

TEST_CASE("InvertColor", "[Color]") {
  REQUIRE(InvertColor(White) == Black);
  REQUIRE(InvertColor(Black) == White);
  REQUIRE(InvertColor(Empty) == Empty);
}
