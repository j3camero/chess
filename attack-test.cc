#include "attack.h"
#include "board.h"
#include "catch.hpp"
#include "color.h"
#include "fen.h"
#include "std.h"

TEST_CASE("Attack detection: opening position", "[Attack]") {
  const string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  const Board b = FenToBoard(fen);
  REQUIRE(IsSquareUnderAttackByColor(b, Point("e3"), White));
  REQUIRE_FALSE(IsSquareUnderAttackByColor(b, Point("e3"), Black));
  REQUIRE(IsSquareUnderAttackByColor(b, Point("e6"), Black));
  REQUIRE_FALSE(IsSquareUnderAttackByColor(b, Point("e6"), White));
  REQUIRE_FALSE(IsSquareUnderAttackByColor(b, Point("e5"), White));
  REQUIRE_FALSE(IsSquareUnderAttackByColor(b, Point("e5"), Black));
}

TEST_CASE("Attack detection: diagonal attack against back rank", "[Attack]") {
  const string fen = "8/8/b7/8/8/8/PPPP1PPP/RNBQKBNR b KQkq - 0 1";
  const Board b = FenToBoard(fen);
  REQUIRE(IsSquareUnderAttackByColor(b, Point("f1"), Black));
  REQUIRE_FALSE(IsSquareUnderAttackByColor(b, Point("f1"), White));
  REQUIRE_FALSE(IsSquareUnderAttackByColor(b, Point("e1"), Black));
  REQUIRE_FALSE(IsSquareUnderAttackByColor(b, Point("e1"), White));
  REQUIRE_FALSE(IsSquareUnderAttackByColor(b, Point("g1"), Black));
  REQUIRE_FALSE(IsSquareUnderAttackByColor(b, Point("g1"), White));
  REQUIRE(IsSquareUnderAttackByColor(b, Point("a6"), White));
  REQUIRE_FALSE(IsSquareUnderAttackByColor(b, Point("a6"), Black));
}

TEST_CASE("Attack detection: all piece types", "[Attack]") {
  // Board position designed to exercise as many different cases as possible.
  // Pawn - both colors & directions, off board
  // Knight - various directions & off board
  // King - various directions
  // Sliding pieces (rook, bishop, queen) - block by friend, block by enemy
  const string fen = "1n3n2/1p3p2/R2Q2bk/8/8/r2q2B1/1P2KP2/P1N5 w KQkq - 0 1";
  const Board b = FenToBoard(fen);
  int expectedWhiteAttacks[8][8] = {
    {1, 1, 0, 1, 0, 1, 0, 0},
    {1, 0, 1, 1, 1, 0, 0, 0},
    {0, 1, 1, 0, 1, 1, 1, 0},
    {1, 0, 1, 1, 1, 0, 0, 0},
    {1, 1, 0, 1, 0, 1, 0, 1},
    {1, 1, 1, 1, 1, 1, 0, 0},
    {1, 0, 0, 1, 0, 0, 0, 1},
    {0, 0, 0, 1, 1, 1, 0, 0}
  };
  int expectedBlackAttacks[8][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 1, 1},
    {1, 0, 1, 1, 1, 0, 0, 0},
    {1, 1, 0, 1, 0, 1, 1, 1},
    {1, 0, 1, 1, 1, 0, 0, 0},
    {0, 1, 1, 0, 1, 1, 1, 0},
    {1, 0, 1, 1, 1, 0, 0, 0},
    {1, 1, 0, 1, 0, 0, 0, 0}
  };
  for (int rank = 0; rank < 8; rank++) {
    for (int file = 0; file < 8; file++) {
      Point p(rank, file);
      bool whiteAttack = IsSquareUnderAttackByColor(b, p, White);
      bool blackAttack = IsSquareUnderAttackByColor(b, p, Black);
      char c = PieceToChar(b.color[rank][file], b.piece[rank][file]);
      REQUIRE(whiteAttack == (bool)expectedWhiteAttacks[rank][file]);
      REQUIRE(blackAttack == (bool)expectedBlackAttacks[rank][file]);
    }
  }
}
