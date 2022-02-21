#ifndef _BOARD_H_
#define _BOARD_H_

#include "piece.h"

// Represents a board position.
struct Board {
  // Store the positions of the pieces on the chessboard.
  Piece squares[8][8];

  // Whose turn it is to move.
  Color move;

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
};

#endif
