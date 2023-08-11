#include "move.h"
#include "piece.h"
#include "std.h"

Move::Move(Point from, Point to) : from(from), to(to) {}

Move::Move(const string& s) {
  if (s.length() != 4) {
    throw "Invalid move string format. Must be formatted like e2e4.";
  }
  from = Point(s.substr(0, 2));
  to = Point(s.substr(2));
}

string Move::ToString() const {
  return from.ToString() + to.ToString();
}

bool Move::operator==(const Move& other) const {
  return (this->from == other.from) && (this->to == other.to);
}

bool Move::operator!=(const Move& other) const {
  return !(*this == other);
}

vector<string> MovesToStrings(const vector<Move>& moves) {
  vector<string> moveStrings;
  for (const Move& move : moves) {
    const string s = move.ToString();
    moveStrings.push_back(s);
  }
  sort(moveStrings.begin(), moveStrings.end());
  return moveStrings;
}
