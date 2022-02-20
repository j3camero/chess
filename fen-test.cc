#include "catch.hpp"
#include "board.h"
#include "fen.h"
#include "piece.h"

TEST_CASE("Read default start position", "[FEN]") {
  const string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  Board b = FenToBoard(fen);
  REQUIRE(b.squares[0][0] == BlackRook);
  REQUIRE(b.squares[0][7] == BlackRook);
  REQUIRE(b.squares[7][0] == WhiteRook);
  REQUIRE(b.squares[7][7] == WhiteRook);
}

TEST_CASE("Read position with only one piece", "[FEN]") {
  const string fen = "8/8/8/2k5/8/8/8/8 w KQkq - 0 1";
  Board b = FenToBoard(fen);
  REQUIRE(b.squares[3][2] == BlackKing);
  REQUIRE(b.squares[3][3] == Empty);
  REQUIRE(b.squares[3][1] == Empty);
  REQUIRE(b.squares[2][2] == Empty);
  REQUIRE(b.squares[4][2] == Empty);
}
