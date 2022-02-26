#include "point.h"
#include "std.h"
#include "string-util.h"

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

bool Point::operator==(const Point& other) const {
  return (this->rank == other.rank) && (this->file == other.file);
}

bool Point::operator!=(const Point& other) const {
  return !(*this == other);
}
