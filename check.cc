#include "attack.h"
#include "board.h"
#include "check.h"
#include "color.h"
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
