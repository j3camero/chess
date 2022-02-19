#ifndef _BOARD_H_
#define _BOARD_H_

#include "std.h"

// Represents a board position.
class Board {
 public:
  // Initialize the default chess opening position.
  Board();

  // Initialize a position based on a string in FEN format.
  Board(const string& fen);

  // Define the different types of pieces there are in chess.
  enum Piece {
    WhitePawn, WhiteKnight, WhiteBishop, WhiteRook, WhiteQueen, WhiteKing,
    BlackPawn, BlackKnight, BlackBishop, BlackRook, BlackQueen, BlackKing,
    Empty
  };

  // Define the two colors of pieces in chess.
  enum Color {White, Black};

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
  int halfMoveClock;

  // Starts at 1 and is incremented after every Black move.
  int fullMoveNumber;

 private:
  // Initialize a position based on a string in FEN format.
  void SetupFen(const string& fen);
};

#endif
