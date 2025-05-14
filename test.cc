#include "assert.h"
#include "attack.h"
#include "check.h"
#include "color.h"
#include "fen.h"
#include "irreversible.h"
#include "move.h"
#include "movegen.h"
#include "std.h"

int main() {
  TestAssert();
  TestAttack();
  TestCheck();
  TestColor();
  TestFen();
  TestIrreversible();
  TestMove();
  TestMovegen();
  cout << "All " << GetAssertCount() << " tests pass :)" << endl;
  return 0;
}
