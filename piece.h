#ifndef _PIECE_H_
#define _PIECE_H_

// Define the different types of pieces there are in chess.
enum Piece {
  WhitePawn, WhiteKnight, WhiteBishop, WhiteRook, WhiteQueen, WhiteKing,
  BlackPawn, BlackKnight, BlackBishop, BlackRook, BlackQueen, BlackKing,
  Empty
};

// Define the two colors of pieces in chess.
enum Color {White, Black};

// Gets the color of a piece.
Color PieceColor(Piece p);

// Gets a human-readable FEN character to represent a chess piece.
char PieceToChar(Piece p);

// Read a chess piece from a character in FEN notation.
Piece CharToPiece(char c);

#endif
