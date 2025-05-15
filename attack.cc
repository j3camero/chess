#include "attack.h"
#include "fen.h"
#include "piece-moves.h"
#include "test.h"

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
    if (from.IsOnBoard() &&
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
    if (from.IsOnBoard() &&
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
  if (!p.IsOnBoard()) {
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
  if (b.color[p.rank][p.file] == attacker) {
    return false;
  }
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
