#include "catch.hpp"
#include "point.h"

TEST_CASE("Default constructor", "[Point]") {
  Point p;
  p.rank = 7;
  REQUIRE(p.rank == 7);
}

TEST_CASE("Basic constructor", "[Point]") {
  Point p(1, 4);
  REQUIRE(p.rank == 1);
  REQUIRE(p.file == 4);
}

TEST_CASE("String constructor e2", "[Point]") {
  Point p("e2");
  REQUIRE(p.rank == 6);
  REQUIRE(p.file == 4);
}

TEST_CASE("String constructor h6", "[Point]") {
  Point p("h6");
  REQUIRE(p.rank == 2);
  REQUIRE(p.file == 7);
}

TEST_CASE("ToString", "[Point]") {
  REQUIRE(Point(7, 0).ToString() == "a1");
  REQUIRE(Point("b7").ToString() == "b7");
  REQUIRE(Point("f5").ToString() == "f5");
}

TEST_CASE("String constructor fail", "[Point]") {
  REQUIRE_THROWS(Point("i5"));
  REQUIRE_THROWS(Point("47"));
  REQUIRE_THROWS(Point("ab"));
  REQUIRE_THROWS(Point("h6x"));
}

TEST_CASE("Equality operator (Point)", "[Point]") {
  REQUIRE(Point("e4") == Point("e4"));
  REQUIRE(Point("e4") != Point("e3"));
  REQUIRE(Point("e4") != Point("d4"));
  REQUIRE(Point("b6") != Point("c7"));
  REQUIRE(Point(3, 4) == Point(3, 4));
  REQUIRE(Point(3, 4) != Point(2, 4));
  REQUIRE(Point(3, 4) != Point(3, 5));
}
