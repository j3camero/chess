#ifndef _FEN_H_
#define _FEN_H_

#include "board.h"
#include "std.h"

// Reads a string in FEN format. Returns a Board position.
Board FenToBoard(const string& fen);

// Returns a FEN string that represents the given board position.
string BoardToFen(const Board& b);

#endif
