#ifndef _COLOR_H_
#define _COLOR_H_

#include "std.h"

// Define the two colors of pieces in chess. Three including "empty" as a color.
enum Color {White, Black, Empty};

// Reverses a color. White -> Black, Black -> White, and Empty -> Empty.
Color InvertColor(Color c);

// Returns the name of each color as a string like "White" "Black" or "Empty"
string ColorToString(Color c);

#endif
