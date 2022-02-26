#ifndef _MOVEGEN_H_
#define _MOVEGEN_H_

#include "board.h"
#include "move.h"
#include "std.h"

// Generate all pseudo-legal moves from a board position. Pseudo-legal means
// that this function does not check for check.
vector<Move> GeneratePseudoLegalMoves(const Board& board);

// Converts a list of moves to a list of strings.
vector<string> MovesToStrings(const vector<Move>& moves);

#endif
