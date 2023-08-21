// Defines the directions that each pieces can move.
#ifndef _PIECE_MOVES_H_
#define _PIECE_MOVES_H_

#include "move.h"
#include "point.h"

// Possible move directions for each piece type.
extern Point knightMoves[8];
extern Point rookMoves[4];
extern Point bishopMoves[4];
extern Point queenMoves[8];

// Important squares on the chessboard.
extern Point a1;
extern Point b1;
extern Point c1;
extern Point d1;
extern Point e1;
extern Point f1;
extern Point g1;
extern Point h1;
extern Point a8;
extern Point b8;
extern Point c8;
extern Point d8;
extern Point e8;
extern Point f8;
extern Point g8;
extern Point h8;

// Castle moves.
extern Move whiteKingCastle;
extern Move whiteQueenCastle;
extern Move blackKingCastle;
extern Move blackQueenCastle;

#endif
