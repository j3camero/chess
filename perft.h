// Code for calculating whether a square is under attack.
#ifndef _PERFT_H_
#define _PERFT_H_

#include "board.h"
#include "std.h"

uint64_t Perft(Board& b, int depth);
uint64_t PerftWithDebugOutput(Board& b, int depth);
uint64_t PerftWithMemory(Board& b, int depth);

#endif
