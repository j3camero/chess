#include "catch.hpp"
#include "point.h"

TEST_CASE("Basic constructor", "[Point]") {
  Point p(1, 4);
  REQUIRE(p.rank == 1);
  REQUIRE(p.file == 4);
}

TEST_CASE("String constructor e2", "[Point]") {
  Point p("e2");
  REQUIRE(p.rank == 1);
  REQUIRE(p.file == 4);
}

TEST_CASE("String constructor h6", "[Point]") {
  Point p("h6");
  REQUIRE(p.rank == 5);
  REQUIRE(p.file == 7);
}

TEST_CASE("String constructor fail", "[Point]") {
  REQUIRE_THROWS(Point("i5"));
  REQUIRE_THROWS(Point("47"));
  REQUIRE_THROWS(Point("ab"));
  REQUIRE_THROWS(Point("h6x"));
}
