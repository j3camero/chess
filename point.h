// A zero-based coordinate system for the squares on a chessboard.
// Zero-based is a bit unintuitive.
//   e2 -> (1, 4)
//   h6 -> (5, 7)
#ifndef _POINT_H_
#define _POINT_H_

#include "std.h"

struct Point {
  // Initialize a point.
  Point(int rank, int file);

  // Initialize a point based on a chess string like "e2" or "h6".
  Point(const string& s);

  // The zero-based rank, from 0 to 7.
  int rank;

  // The zero-based file, from 0 to 7.
  int file;
};

#endif
