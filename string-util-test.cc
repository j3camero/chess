#include "std.h"
#include "string-util.h"
#include "test.h"

TEST(StringSplitThreeItems) {
  vector<string> tokens = StringUtil::Split("one,two,three", ',');
  ASSERT(tokens.size() == 3);
  ASSERT(tokens[0] == "one");
  ASSERT(tokens[1] == "two");
  ASSERT(tokens[2] == "three");
}

TEST(StringSplitChangeDelimiter) {
  vector<string> tokens = StringUtil::Split("one|two| ,", '|');
  ASSERT(tokens.size() == 3);
  ASSERT(tokens[0] == "one");
  ASSERT(tokens[1] == "two");
  ASSERT(tokens[2] == " ,");
}

TEST(StringSplitWithOnlyOneItem) {
  vector<string> tokens = StringUtil::Split("word", ',');
  ASSERT(tokens.size() == 1);
  ASSERT(tokens[0] == "word");
}

TEST(StringSplitWithEmptyItems) {
  vector<string> tokens = StringUtil::Split(",,", ',');
  ASSERT(tokens.size() == 3);
  ASSERT(tokens[0] == "");
  ASSERT(tokens[1] == "");
  ASSERT(tokens[2] == "");
}

TEST(StringSplitEmptyString) {
  vector<string> tokens = StringUtil::Split("", ',');
  ASSERT(tokens.size() == 1);
  ASSERT(tokens[0] == "");
}

TEST(IsDigitTrue) {
  ASSERT(StringUtil::IsDigit('0'));
  ASSERT(StringUtil::IsDigit('1'));
  ASSERT(StringUtil::IsDigit('5'));
  ASSERT(StringUtil::IsDigit('8'));
  ASSERT(StringUtil::IsDigit('9'));
}

TEST(IsDigitFalse) {
  ASSERT(!StringUtil::IsDigit('a'));
  ASSERT(!StringUtil::IsDigit('Z'));
  ASSERT(!StringUtil::IsDigit('/'));
  ASSERT(!StringUtil::IsDigit(':'));
  ASSERT(!StringUtil::IsDigit('+'));
}

TEST(DigitToIntVariousCases) {
  ASSERT(StringUtil::DigitToInt('0') == 0);
  ASSERT(StringUtil::DigitToInt('1') == 1);
  ASSERT(StringUtil::DigitToInt('7') == 7);
  ASSERT(StringUtil::DigitToInt('9') == 9);
}
