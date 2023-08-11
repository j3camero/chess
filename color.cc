#include "color.h"

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
