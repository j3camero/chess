#ifndef _BOARD_H_
#define _BOARD_H_

#include "color.h"
#include "piece.h"
#include "point.h"
#include "irreversible.h"

// Represents a board position.
struct Board {
  // The color of each square - White, Black, or Empty.
  Color color[8][8];

  // Which type of piece is on each square.
  Piece piece[8][8];

  // Whose turn it is to move.
  Color turn;

  // Opponent color. Always the opposite of turn.
  Color opp;

  // Starts at 1 and is incremented after every Black move.
  int moveCount;

  // Castling rights, en passant file, and half-move clock are grouped together
  // into a single struct, called Irreversible. It is kept small enough that they
  // can be copied together in one machine instruction. These are the
  // irreversible aspects of chess game state. They are copied rather than
  // being incrementally updated.
  Irreversible irreversible;

  // Stores the locations of both kings.
  Point whiteKingLocation;
  Point blackKingLocation;
};

#endif
