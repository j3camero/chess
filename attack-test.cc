#include "attack.h"
#include "fen.h"
#include "test.h"

TEST(AttackDetectionOpeningPosition) {
  const string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  const Board b = FenToBoard(fen);
  ASSERT(IsSquareUnderAttackByColor(b, Point("e3"), White));
  ASSERT(!IsSquareUnderAttackByColor(b, Point("e3"), Black));
  ASSERT(IsSquareUnderAttackByColor(b, Point("e6"), Black));
  ASSERT(!IsSquareUnderAttackByColor(b, Point("e6"), White));
  ASSERT(!IsSquareUnderAttackByColor(b, Point("e5"), White));
  ASSERT(!IsSquareUnderAttackByColor(b, Point("e5"), Black));
}

TEST(AttackDetectionDiagonalAttackAgainstBackRank) {
  const string fen = "8/8/b7/8/8/8/PPPP1PPP/RNBQKBNR b KQkq - 0 1";
  const Board b = FenToBoard(fen);
  ASSERT(IsSquareUnderAttackByColor(b, Point("f1"), Black));
  ASSERT(!IsSquareUnderAttackByColor(b, Point("f1"), White));
  ASSERT(!IsSquareUnderAttackByColor(b, Point("e1"), Black));
  ASSERT(!IsSquareUnderAttackByColor(b, Point("e1"), White));
  ASSERT(!IsSquareUnderAttackByColor(b, Point("g1"), Black));
  ASSERT(!IsSquareUnderAttackByColor(b, Point("g1"), White));
  ASSERT(IsSquareUnderAttackByColor(b, Point("a6"), White));
  ASSERT(!IsSquareUnderAttackByColor(b, Point("a6"), Black));
}

TEST(AttackAllPieceTypes) {
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
      //char c = PieceToChar(b.color[rank][file], b.piece[rank][file]);
      ASSERT(whiteAttack == (bool)expectedWhiteAttacks[rank][file]);
      ASSERT(blackAttack == (bool)expectedBlackAttacks[rank][file]);
    }
  }
}
