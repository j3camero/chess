#include "point.h"
#include "std.h"
#include "string-util.h"

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
  rank = StringUtil::DigitToInt(r) - 1;
  if (rank < 0 || rank >= 8) {
    throw ("Invalid chessboard coordinate " + s +
	   ". Rank must be a digit in the range [1-8].");
  }
}
