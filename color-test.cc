#include "color.h"
#include "test.h"

TEST(InvertWhite) {
  ASSERT(InvertColor(White) == Black);
}

TEST(InvertBlack) {
  ASSERT(InvertColor(Black) == White);
}

TEST(InvertEmpty) {
  ASSERT(InvertColor(Empty) == Empty);
}
