#include "color.h"
#include "test.h"

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

TEST(InvertWhite) {
  ASSERT(InvertColor(White) == Black);
}

TEST(InvertBlack) {
  ASSERT(InvertColor(Black) == White);
}

TEST(InvertEmpty) {
  ASSERT(InvertColor(Empty) == Empty);
}
