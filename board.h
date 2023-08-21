#ifndef _BOARD_H_
#define _BOARD_H_

#include "color.h"
#include "piece.h"
#include "point.h"

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

  // Castling availability.
  bool whiteKingCastle;
  bool whiteQueenCastle;
  bool blackKingCastle;
  bool blackQueenCastle;

  // En-passant target file. -1 if no en-passant capture is available.
  int enPassantFile;

  // Halfmove clock for the fifty-move rule.
  int halfmoveClock;

  // Starts at 1 and is incremented after every Black move.
  int moveCount;

  // Stores the locations of both kings.
  Point whiteKingLocation;
  Point blackKingLocation;
};

#endif
