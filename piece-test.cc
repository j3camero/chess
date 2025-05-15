#include "color.h"
#include "piece.h"
#include "test.h"

TEST(PieceToCharExamples) {
  ASSERT(PieceToChar(White, King) == 'K');
  ASSERT(PieceToChar(Black, Pawn) == 'p');
}

TEST(CharToPieceWhiteRook) {
  Color c;
  Piece p;
  CharToPiece('R', c, p);
  ASSERT(c == White);
  ASSERT(p == Rook);
}

TEST(CharToPieceBlackRook) {
  Color c;
  Piece p;
  CharToPiece('r', c, p);
  ASSERT(c == Black);
  ASSERT(p == Rook);
}

TEST(CharToPieceBlackKnight) {
  Color c;
  Piece p;
  CharToPiece('n', c, p);
  ASSERT(c == Black);
  ASSERT(p == Knight);
}
