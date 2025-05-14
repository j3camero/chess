#include "assert.h"
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

void TestColor() {
  ASSERT(InvertColor(White) == Black);
  ASSERT(InvertColor(Black) == White);
  ASSERT(InvertColor(Empty) == Empty);
}
