#include "move.h"
#include "piece.h"
#include "point.h"
#include "std.h"
#include "test.h"

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
