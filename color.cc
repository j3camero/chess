#include "color.h"
#include "std.h"

Color InvertColor(Color c) {
  switch (c) {
  case White:
    return Black;
  case Black:
    return White;
  case Empty:
    return Empty;
  }
  throw "Unknown color";
}

string ColorToString(Color c) {
  switch (c) {
  case White:
    return "White";
  case Black:
    return "Black";
  case Empty:
    return "Empty";
  }
  throw "Unknown color";
}
