#include "catch.hpp"
#include "piece.h"

TEST_CASE("PieceColor", "[Piece]") {
  REQUIRE(PieceColor(WhiteKing) == White);
  REQUIRE(PieceColor(BlackPawn) == Black);
}

TEST_CASE("InvertColor", "[Piece]") {
  REQUIRE(InvertColor(White) == Black);
  REQUIRE(InvertColor(Black) == White);
}

TEST_CASE("PieceToChar", "[Piece]") {
  REQUIRE(PieceToChar(WhiteKing) == 'K');
  REQUIRE(PieceToChar(BlackPawn) == 'p');
}

TEST_CASE("CharToPiece", "[Piece]") {
  REQUIRE(CharToPiece('R') == WhiteRook);
  REQUIRE(CharToPiece('r') == BlackRook);
}
