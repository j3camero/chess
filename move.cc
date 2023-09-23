#include "move.h"
#include "piece.h"
#include "std.h"

Move::Move(
  Point from,
  Point to,
  bool isCapture,
  Piece capturedPiece,
  bool isPromotion,
  Piece promotionPiece) :
  from(from),
  to(to),
  isCapture(isCapture),
  capturedPiece(capturedPiece),
  isPromotion(isPromotion),
  promotionPiece(promotionPiece) {}

Move::Move(const string& s, bool isCapture, Piece capturedPiece) :
  isCapture(isCapture),
  capturedPiece(capturedPiece) {
  int n = s.length();
  if (n != 4 && n != 5) {
    throw "Invalid move string format. Must be formatted like e2e4.";
  }
  from = Point(s.substr(0, 2));
  to = Point(s.substr(2, 2));
  isPromotion = false;
  promotionPiece = Pawn;
  if (s.length() == 5) {
    char fifth = s[4];
    isPromotion = true;
    Color unusedColor;
    CharToPiece(fifth, unusedColor, promotionPiece);
  }
}

string Move::ToString() const {
  string s = from.ToString() + to.ToString();
  if (isPromotion) {
    char promotionChar = PieceToChar(Black, promotionPiece);
    string promotionString(1, promotionChar);
    s += promotionString;
  }
  return s;
}

bool Move::operator==(const Move& other) const {
  return (this->from == other.from) &&
         (this->to == other.to) &&
         (this->isPromotion == other.isPromotion) &&
         (this->promotionPiece == other.promotionPiece) &&
         (this->isCapture == other.isCapture) &&
         (this->capturedPiece == other.capturedPiece);
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
