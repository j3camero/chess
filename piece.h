#ifndef _PIECE_H_
#define _PIECE_H_

#include "color.h"

// Define the different types of pieces there are in chess.
enum Piece {Pawn, Knight, Bishop, Rook, Queen, King};

// Gets a human-readable FEN character to represent a chess piece.
char PieceToChar(Color c, Piece p);

// Read a chess piece from a character in FEN notation.
// c (input): an ASCII character
// color (output): the color represented by the character.
// piece (output): the piece type represented by the character.
void CharToPiece(char c, Color& color, Piece& piece);

#endif
