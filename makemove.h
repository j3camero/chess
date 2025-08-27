#ifndef _MAKEMOVE_H_
#define _MAKEMOVE_H_

#include "board.h"
#include "irreversible.h"
#include "move.h"

void MakeMove(Board& b, const Move& m);
void UndoMove(Board& b, const Move& m, const Irreversible i);

#endif
