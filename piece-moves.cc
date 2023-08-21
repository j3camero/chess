#include "piece-moves.h"

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
