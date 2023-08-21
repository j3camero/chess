// Code for calculating whether a square is under attack.
#ifndef _ATTACK_H_
#define _ATTACK_H_

#include "board.h"
#include "color.h"
#include "point.h"

// Returns true if square p is under attack by a piece of the specified color.
bool IsSquareUnderAttackByColor(const Board& b, const Point& p, Color attacker);

#endif
