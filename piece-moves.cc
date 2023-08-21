#include "move.h"
#include "piece-moves.h"
#include "point.h"

Point knightMoves[8] = {
  Point(1, 2), Point(2, 1), Point(2, -1), Point(1, -2),
  Point(-1, -2), Point(-2, -1), Point(-2, 1), Point(-1, 2)
};
Point rookMoves[4] = {
  Point(1, 0), Point(0, 1), Point(-1, 0), Point(0, -1)
};
Point bishopMoves[4] = {
  Point(1, 1), Point(-1, 1), Point(1, -1), Point(-1, -1)
};
Point queenMoves[8] = {
  Point(1, 0), Point(0, 1), Point(-1, 0), Point(0, -1),
  Point(1, 1), Point(-1, 1), Point(1, -1), Point(-1, -1)
};
Point a1(7, 0);
Point b1(7, 1);
Point c1(7, 2);
Point d1(7, 3);
Point e1(7, 4);
Point f1(7, 5);
Point g1(7, 6);
Point h1(7, 7);
Point a8(0, 0);
Point b8(0, 1);
Point c8(0, 2);
Point d8(0, 3);
Point e8(0, 4);
Point f8(0, 5);
Point g8(0, 6);
Point h8(0, 7);
Move whiteKingCastle(e1, g1);
Move whiteQueenCastle(e1, c1);
Move blackKingCastle(e8, g8);
Move blackQueenCastle(e8, c8);
