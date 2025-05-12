#include "board.h"
#include "check.h"
#include "color.h"
#include "fen.h"
#include "std.h"

void TestCheckOpeningPosition() {
  const string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  const Board b = FenToBoard(fen);
  assert(!IsWhiteKingInCheck(b));
  assert(!IsBlackKingInCheck(b));
  assert(!IsSideToMoveInCheck(b));
  assert(!IsOppInCheck(b));
}

void TestCheckDiagonalAttackAgainstBackRank() {
  const string fen = "8/8/b7/8/8/8/PPPP1PPP/RNBQKBNR b KQkq - 0 1";
  const Board b = FenToBoard(fen);
  assert(!IsWhiteKingInCheck(b));
  assert(!IsBlackKingInCheck(b));
  assert(!IsSideToMoveInCheck(b));
  assert(!IsOppInCheck(b));
}

void TestCheckAllPiecesTypes() {
  const string fen = "1n3n2/1p3p2/R2Q2bk/8/8/r2q2B1/1P2KP2/P1N5 w KQkq - 0 1";
  const Board b = FenToBoard(fen);
  assert(IsWhiteKingInCheck(b));
  assert(!IsBlackKingInCheck(b));
  assert(IsSideToMoveInCheck(b));
  assert(!IsOppInCheck(b));
}

void TestCheck() {
  TestCheckOpeningPosition();
  TestCheckDiagonalAttackAgainstBackRank();
  TestCheckAllPiecesTypes();
}
