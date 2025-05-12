#include "assert.h"
#include "check.h"
#include "std.h"

int main() {
  SetAssertCount(0);
  TestAssert();
  TestCheck();
  cout << "All " << GetAssertCount() << " tests pass :)" << endl;
  return 0;
}
