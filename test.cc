#include "std.h"
#include "test.h"

// The assert counter counts how many times ASSERT is called.
int assertCount = 0;

void IncrementAssertCount() {
  assertCount++;
}

int GetAssertCount() {
    return assertCount;
}

// Example unit test showing how to use ASSERT.
TEST(ASSERT) {
  ASSERT(2 + 2 == 4);
}

// Test that calling ASSERT increments the assert counter behind the scenes.
TEST(IncrementAssertCount) {
  int before = GetAssertCount();
  ASSERT(2 + 2 == 4);
  int after = GetAssertCount();
  ASSERT(after == before + 1);
}

// Unit tests declared using TEST() run before main(). If any of the unit tests
// fail they abort the program execution before it reaches main(). Therefore
// by the time this main() function runs it means all the unit tests already
// ran and passed. Great success! All that's left for this main() function to
// do is to report how many tests ran & passed.
int main() {
  cout << "All " << GetAssertCount() << " tests pass :)" << endl;
  return 0;
}
