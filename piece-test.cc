#include "catch.hpp"
#include "color.h"
#include "piece.h"

TEST_CASE("PieceToChar", "[Piece]") {
  REQUIRE(PieceToChar(White, King) == 'K');
  REQUIRE(PieceToChar(Black, Pawn) == 'p');
}

TEST_CASE("CharToPiece", "[Piece]") {
  Color c;
  Piece p;
  CharToPiece('R', c, p);
  REQUIRE(c == White);
  REQUIRE(p == Rook);
  CharToPiece('r', c, p);
  REQUIRE(c == Black);
  REQUIRE(p == Rook);
  CharToPiece('n', c, p);
  REQUIRE(c == Black);
  REQUIRE(p == Knight);
}
