#include "attack.h"
#include "piece-moves.h"

bool IsSquareUnderAttackByPawn(const Board& b, const Point& p, Color attacker) {
  // Opposite of usual move direction because we're searching backwards along
  // the direction of attack.
  const int dir = (attacker == White) ? 1 : -1;
  const int oneRankForward = p.rank + dir;
  if (oneRankForward >= 0 && oneRankForward < 8) {
    if (p.file > 0) {
      const int oneFileLeft = p.file - 1;
      if (b.color[oneRankForward][oneFileLeft] == attacker &&
          b.piece[oneRankForward][oneFileLeft] == Pawn) {
        return true;
      }
    }
    if (p.file < 7) {
      const int oneFileRight = p.file + 1;
      if (b.color[oneRankForward][oneFileRight] == attacker &&
          b.piece[oneRankForward][oneFileRight] == Pawn) {
        return true;
      }
    }
  }
  return false;
}

bool IsSquareUnderAttackByKnight(const Board& b,
                                 const Point& p,
                                 Color attacker) {
  for (const Point& k : knightMoves) {
    Point from = p + k;
    if (from.rank >= 0 && from.rank < 8 &&
        from.file >= 0 && from.file < 8 &&
        b.color[from.rank][from.file] == attacker &&
        b.piece[from.rank][from.file] == Knight) {
      return true;
    }
  }
  return false;
}

bool IsSquareUnderAttackByKing(const Board& b, const Point& p, Color attacker) {
  for (const Point& direction : queenMoves) {
    Point from = p + direction;
    if (from.rank >= 0 && from.rank < 8 &&
        from.file >= 0 && from.file < 8 &&
        b.color[from.rank][from.file] == attacker &&
        b.piece[from.rank][from.file] == King) {
      return true;
    }
  }
  return false;
}

bool FindSlidingPiece(const Board& b,
                      const Point& p,
                      const Point& direction,
                      Color attacker,
                      Piece nonQueenPiece) {
  if (p.rank < 0 || p.rank > 7 || p.file < 0 || p.file > 7) {
    return false;
  }
  const Color c = b.color[p.rank][p.file];
  if (c == attacker) {
    const Piece piece = b.piece[p.rank][p.file];
    return (piece == Queen) || (piece == nonQueenPiece);
  }
  if (c == Empty) {
    const Point next = p + direction;
    return FindSlidingPiece(b, next, direction, attacker, nonQueenPiece);
  }
  return false;
}

bool IsSquareUnderAttackByRook(const Board& b, const Point& p, Color attacker) {
  for (const Point& direction : rookMoves) {
    Point next = p + direction;
    if (FindSlidingPiece(b, next, direction, attacker, Rook)) {
      return true;
    }
  }
  return false;
}

bool IsSquareUnderAttackByBishop(const Board& b,
                                 const Point& p,
                                 Color attacker) {
  for (const Point& direction : bishopMoves) {
    Point next = p + direction;
    if (FindSlidingPiece(b, next, direction, attacker, Bishop)) {
      return true;
    }
  }
  return false;
}

bool IsSquareUnderAttackByColor(const Board& b,
                                const Point& p,
                                Color attacker) {
  if (IsSquareUnderAttackByPawn(b, p, attacker)) {
    return true;
  }
  if (IsSquareUnderAttackByKnight(b, p, attacker)) {
    return true;
  }
  if (IsSquareUnderAttackByKing(b, p, attacker)) {
    return true;
  }
  if (IsSquareUnderAttackByRook(b, p, attacker)) {
    return true;
  }
  if (IsSquareUnderAttackByBishop(b, p, attacker)) {
    return true;
  }
  return false;
}
