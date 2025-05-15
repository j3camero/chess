#include "point.h"
#include "std.h"
#include "string-util.h"
#include "test.h"

Point::Point() : rank(-1), file(-1) {}

Point::Point(int rank, int file) : rank(rank), file(file) {}

Point::Point(const string& s) {
  if (s.size() != 2) {
    throw ("Invalid chessboard coordinate " + s +
	   ". Must be a letter and a digit.");
  }
  const char f = s[0];
  if (f >= 'a' && f <= 'h') {
    file = f - 'a';
  } else {
    throw ("Invalid chessboard coordinate " + s +
	   ". File must be in the range [a-h].");
  }
  const char r = s[1];
  if (!StringUtil::IsDigit(r)) {
    throw "Invalid chessboard coordinate " + s + ". Rank must be a digit.";
  }
  rank = 8 - StringUtil::DigitToInt(r);
  if (rank < 0 || rank >= 8) {
    throw ("Invalid chessboard coordinate " + s +
	   ". Rank must be a digit in the range [1-8].");
  }
}

string Point::ToString() const {
  char fileChar = 'a' + file;
  string fileString(1, fileChar);
  string rankString = to_string(8 - rank);
  return fileString + rankString;
}

bool Point::IsOnBoard() const {
  return (rank >= 0) && (rank < 8) && (file >= 0) && (file < 8);
}

bool Point::operator==(const Point& other) const {
  return (this->rank == other.rank) && (this->file == other.file);
}

bool Point::operator!=(const Point& other) const {
  return !(*this == other);
}

Point Point::operator+(const Point& other) const {
  return Point(this->rank + other.rank, this->file + other.file);
}

Point& Point::operator+=(const Point& other) {
  this->rank += other.rank;
  this->file += other.file;
  return *this;
}

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
