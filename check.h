// Code for calculating whether the king is in check.
#ifndef _CHECK_H_
#define _CHECK_H_

#include "board.h"
#include "color.h"

bool IsWhiteKingInCheck(const Board& b);
bool IsBlackKingInCheck(const Board& b);
bool IsSideToMoveInCheck(const Board& b);
bool IsOppInCheck(const Board& b);

#endif
