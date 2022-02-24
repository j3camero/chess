#ifndef _MOVE_H_
#define _MOVE_H_

#include "board.h"
#include "point.h"
#include "std.h"

// Encodes a chess move as two points on the board.
// Castling is encoded as the movement of the king piece. The movement of the
// corresponding rook is implied.
// En-passant captures are encoded as the movement of the attacking pawn. The
// removal of the attacked pawn is implicit.
struct Move {
  Move(Point from, Point to);

  Point from;
  Point to;
};

vector<Move> GenerateLegalMoves(const Board& board);

#endif
