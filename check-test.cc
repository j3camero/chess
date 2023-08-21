#include "board.h"
#include "catch.hpp"
#include "check.h"
#include "color.h"
#include "fen.h"
#include "std.h"

TEST_CASE("Check detection: opening position", "[Check]") {
  const string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  const Board b = FenToBoard(fen);
  REQUIRE_FALSE(IsWhiteKingInCheck(b));
  REQUIRE_FALSE(IsBlackKingInCheck(b));
  REQUIRE_FALSE(IsSideToMoveInCheck(b));
  REQUIRE_FALSE(IsOppInCheck(b));
}

TEST_CASE("Check detection: diagonal attack against back rank", "[Check]") {
  const string fen = "8/8/b7/8/8/8/PPPP1PPP/RNBQKBNR b KQkq - 0 1";
  const Board b = FenToBoard(fen);
  REQUIRE_FALSE(IsWhiteKingInCheck(b));
  REQUIRE_FALSE(IsBlackKingInCheck(b));
  REQUIRE_FALSE(IsSideToMoveInCheck(b));
  REQUIRE_FALSE(IsOppInCheck(b));
}

TEST_CASE("Check detection: all piece types", "[Check]") {
  const string fen = "1n3n2/1p3p2/R2Q2bk/8/8/r2q2B1/1P2KP2/P1N5 w KQkq - 0 1";
  const Board b = FenToBoard(fen);
  REQUIRE(IsWhiteKingInCheck(b));
  REQUIRE_FALSE(IsBlackKingInCheck(b));
  REQUIRE(IsSideToMoveInCheck(b));
  REQUIRE_FALSE(IsOppInCheck(b));
}
