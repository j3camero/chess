#include "assert.h"
#include "attack.h"
#include "board.h"
#include "check.h"
#include "color.h"
#include "fen.h"
#include "std.h"

bool IsWhiteKingInCheck(const Board& b) {
  if (b.whiteKingLocation == Point(-1, -1)) {
    return false;
  }
  return IsSquareUnderAttackByColor(b, b.whiteKingLocation, Black);
}

bool IsBlackKingInCheck(const Board& b) {
  if (b.blackKingLocation == Point(-1, -1)) {
    return false;
  }
  return IsSquareUnderAttackByColor(b, b.blackKingLocation, White);
}

bool IsSideToMoveInCheck(const Board& b) {
  if (b.turn == White) {
    return IsWhiteKingInCheck(b);
  } else {
    return IsBlackKingInCheck(b);
  }
}

bool IsOppInCheck(const Board& b) {
  if (b.turn == White) {
    return IsBlackKingInCheck(b);
  } else {
    return IsWhiteKingInCheck(b);
  }
}

void TestOpeningPosition() {
  const string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  const Board b = FenToBoard(fen);
  ASSERT(!IsWhiteKingInCheck(b));
  ASSERT(!IsBlackKingInCheck(b));
  ASSERT(!IsSideToMoveInCheck(b));
  ASSERT(!IsOppInCheck(b));
}

void TestDiagonalAttackAgainstBackRank() {
  const string fen = "8/8/b7/8/8/8/PPPP1PPP/RNBQKBNR b KQkq - 0 1";
  const Board b = FenToBoard(fen);
  ASSERT(!IsWhiteKingInCheck(b));
  ASSERT(!IsBlackKingInCheck(b));
  ASSERT(!IsSideToMoveInCheck(b));
  ASSERT(!IsOppInCheck(b));
}

void TestAllPiecesTypes() {
  const string fen = "1n3n2/1p3p2/R2Q2bk/8/8/r2q2B1/1P2KP2/P1N5 w KQkq - 0 1";
  const Board b = FenToBoard(fen);
  ASSERT(IsWhiteKingInCheck(b));
  ASSERT(!IsBlackKingInCheck(b));
  ASSERT(IsSideToMoveInCheck(b));
  ASSERT(!IsOppInCheck(b));
}

void TestCheck() {
  TestOpeningPosition();
  TestDiagonalAttackAgainstBackRank();
  TestAllPiecesTypes();
}
