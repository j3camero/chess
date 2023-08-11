#ifndef _COLOR_H_
#define _COLOR_H_

// Define the two colors of pieces in chess. Three including "empty" as a color.
enum Color {White, Black, Empty};

// Reverses a color. White -> Black, Black -> White, and Empty -> Empty.
Color InvertColor(Color c);

#endif
