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
  // Basic constructor.
  Move(Point from, Point to);

  // Accepts strings like e2e4 where both squares are fully specified.
  Move(const string& s);

  // Outputs a string representation of the move like g8f6.
  string ToString() const;

  // Equality operator.
  bool operator==(const Move& other) const;
  bool operator!=(const Move& other) const;

  Point from;
  Point to;
};

vector<Move> GenerateLegalMoves(const Board& board);

// Converts a list of moves to a list of strings.
vector<string> MovesToStrings(const vector<Move>& moves);

#endif
