#include "board.h"
#include "check.h"
#include "fen.h"
#include "test.h"

TEST(IsOpeningPositionInCheck) {
  const string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  const Board b = FenToBoard(fen);
  ASSERT(!IsWhiteKingInCheck(b));
  ASSERT(!IsBlackKingInCheck(b));
  ASSERT(!IsSideToMoveInCheck(b));
  ASSERT(!IsOppInCheck(b));
}

TEST(CheckDetectionDiagonalAttackAgainstBackRank) {
  const string fen = "8/8/b7/8/8/8/PPPP1PPP/RNBQKBNR b KQkq - 0 1";
  const Board b = FenToBoard(fen);
  ASSERT(!IsWhiteKingInCheck(b));
  ASSERT(!IsBlackKingInCheck(b));
  ASSERT(!IsSideToMoveInCheck(b));
  ASSERT(!IsOppInCheck(b));
}

TEST(CheckDetectionWithAllPiecesTypes) {
  const string fen = "1n3n2/1p3p2/R2Q2bk/8/8/r2q2B1/1P2KP2/P1N5 w KQkq - 0 1";
  const Board b = FenToBoard(fen);
  ASSERT(IsWhiteKingInCheck(b));
  ASSERT(!IsBlackKingInCheck(b));
  ASSERT(IsSideToMoveInCheck(b));
  ASSERT(!IsOppInCheck(b));
}
