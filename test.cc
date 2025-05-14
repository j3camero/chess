#include "assert.h"
#include "attack.h"
#include "check.h"
#include "std.h"

int main() {
  TestAssert();
  TestAttack();
  TestCheck();
  cout << "All " << GetAssertCount() << " tests pass :)" << endl;
  return 0;
}
