#include "assert.h"
#include "attack.h"
#include "check.h"
#include "color.h"
#include "fen.h"
#include "std.h"

int main() {
  TestAssert();
  TestAttack();
  TestCheck();
  TestColor();
  TestFen();
  cout << "All " << GetAssertCount() << " tests pass :)" << endl;
  return 0;
}
