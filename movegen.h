#ifndef _MOVEGEN_H_
#define _MOVEGEN_H_

#include "board.h"
#include "move.h"
#include "std.h"

// Generate all pseudo-legal moves from a board position. Pseudo-legal means
// that this function does not check for check.
vector<Move> GeneratePseudoLegalMoves(const Board& board);

// Generate all legal moves from a board position. This function checks for
// check which is more expensive than pseudo-legal move generation.
vector<Move> GenerateLegalMoves(Board& board);

#endif
