#include "move.h"
#include "piece.h"
#include "std.h"
#include "test.h"

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

TEST(MoveBasicConstructor) {
  Move move(Point(7, 1), Point(5, 2));
  ASSERT(move.from.rank == 7);
  ASSERT(move.from.file == 1);
  ASSERT(move.to.rank == 5);
  ASSERT(move.to.file == 2);
  ASSERT(!move.isCapture);
  ASSERT(!move.isPromotion);
}

TEST(MoveCapturePromotion) {
  Move move(Point(7, 1), Point(5, 2), true, Bishop, true, Queen);
  ASSERT(move.from.rank == 7);
  ASSERT(move.from.file == 1);
  ASSERT(move.to.rank == 5);
  ASSERT(move.to.file == 2);
  ASSERT(move.isCapture);
  ASSERT(move.capturedPiece == Bishop);
  ASSERT(move.isPromotion);
  ASSERT(move.promotionPiece == Queen);
}

TEST(MoveAlgebraicNotation) {
  Move move("e2e4");
  ASSERT(move.from.rank == 6);
  ASSERT(move.from.file == 4);
  ASSERT(move.to.rank == 4);
  ASSERT(move.to.file == 4);
}

TEST(MoveAlgebraicKnight) {
  Move move("g8f6");
  ASSERT(move.from.rank == 0);
  ASSERT(move.from.file == 6);
  ASSERT(move.to.rank == 2);
  ASSERT(move.to.file == 5);
}

TEST(MoveAlgebraicKnightPromotion) {
  Move move("g7g8n");
  ASSERT(move.from.rank == 1);
  ASSERT(move.from.file == 6);
  ASSERT(move.to.rank == 0);
  ASSERT(move.to.file == 6);
  ASSERT(!move.isCapture);
  ASSERT(move.isPromotion);
  ASSERT(move.promotionPiece == Knight);
}

TEST(MoveAlgebraicQueenPromotion) {
  Move move("g7g8Q");
  ASSERT(move.from.rank == 1);
  ASSERT(move.from.file == 6);
  ASSERT(move.to.rank == 0);
  ASSERT(move.to.file == 6);
  ASSERT(!move.isCapture);
  ASSERT(move.isPromotion);
  ASSERT(move.promotionPiece == Queen);
}

TEST(MoveAlgebraicCapturePromotion) {
  Move move("g7f8Q", true, Rook);
  ASSERT(move.from.rank == 1);
  ASSERT(move.from.file == 6);
  ASSERT(move.to.rank == 0);
  ASSERT(move.to.file == 5);
  ASSERT(move.isCapture);
  ASSERT(move.capturedPiece == Rook);
  ASSERT(move.isPromotion);
  ASSERT(move.promotionPiece == Queen);
}

TEST(MoveEqualityOperator) {
  ASSERT(Move("e2e4") == Move("e2e4"));
  ASSERT(Move("e2e4") != Move("e2e3"));
  ASSERT(Move("e2e4") != Move("d4e4"));
  ASSERT(Move("a3b6") != Move("c7a1"));
  ASSERT(Move("h6f7") == Move(Point(2, 7), Point(1, 5)));
}

TEST(MovesToStrings) {
  const vector<Move> moves = { Move("b1a3"), Move("g8h6") };
  const vector<string> actual = MovesToStrings(moves);
  const vector<string> expected = { "b1a3", "g8h6" };
  ASSERT(actual == expected);
}
