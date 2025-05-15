#include "point.h"
#include "test.h"

TEST(PointDefaultConstructor) {
  Point p;
  p.rank = 7;
  ASSERT(p.rank == 7);
}

TEST(PointBasicConstructor) {
  Point p(1, 4);
  ASSERT(p.rank == 1);
  ASSERT(p.file == 4);
}

TEST(PointStringConstructorE2) {
  Point p("e2");
  ASSERT(p.rank == 6);
  ASSERT(p.file == 4);
}

TEST(PointStringConstructorH6) {
  Point p("h6");
  ASSERT(p.rank == 2);
  ASSERT(p.file == 7);
}

TEST(PointToString) {
  ASSERT(Point(7, 0).ToString() == "a1");
  ASSERT(Point("b7").ToString() == "b7");
  ASSERT(Point("f5").ToString() == "f5");
}

TEST(PointIsOnBoard) {
  ASSERT(Point(0, 0).IsOnBoard());
  ASSERT(Point(1, 0).IsOnBoard());
  ASSERT(Point(0, 1).IsOnBoard());
  ASSERT(Point(7, 0).IsOnBoard());
  ASSERT(Point(0, 7).IsOnBoard());
  ASSERT(Point(7, 7).IsOnBoard());
  ASSERT(Point(2, 3).IsOnBoard());
  ASSERT(Point(6, 4).IsOnBoard());
  ASSERT(!Point(-1, 4).IsOnBoard());
  ASSERT(!Point(6, -2).IsOnBoard());
  ASSERT(!Point(-1, -1).IsOnBoard());
  ASSERT(!Point(8, 4).IsOnBoard());
  ASSERT(!Point(6, 9).IsOnBoard());
  ASSERT(!Point(9, 8).IsOnBoard());
}

TEST(PointStringConstructorFail) {
  ASSERT_EXCEPTION(Point("i5"));
  ASSERT_EXCEPTION(Point("47"));
  ASSERT_EXCEPTION(Point("ab"));
  ASSERT_EXCEPTION(Point("h6x"));
}

TEST(PointEqualityOperator) {
  ASSERT(Point("e4") == Point("e4"));
  ASSERT(Point("e4") != Point("e3"));
  ASSERT(Point("e4") != Point("d4"));
  ASSERT(Point("b6") != Point("c7"));
  ASSERT(Point(3, 4) == Point(3, 4));
  ASSERT(Point(3, 4) != Point(2, 4));
  ASSERT(Point(3, 4) != Point(3, 5));
}

TEST(PointAdditionOperators) {
  ASSERT(Point("e2") + Point(-2, 0) == Point("e4"));
  ASSERT(Point(1, 2) + Point("b6") == Point("d5"));
  Point p(3, 7);
  p += Point(2, -3);
  ASSERT(p == Point(5, 4));
}
