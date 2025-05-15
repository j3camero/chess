#include "std.h"
#include "test.h"

// A list of function pointers to all the unit tests. The TEST macro
// automatically calls RegisterTest to add them to this list.
vector<TestFunction> registry;

// The assert counter counts how many times ASSERT is called.
int assertCount = 0;

void RegisterTest(TestFunction f) {
  registry.push_back(f);
}

void IncrementAssertCount() {
  assertCount++;
}

int GetAssertCount() {
    return assertCount;
}

// Example unit test showing how to use ASSERT.
TEST(AssertExample) {
  ASSERT(2 + 2 == 4);
}

// Test that calling ASSERT increments the assert counter behind the scenes.
TEST(AssertCount) {
  int before = GetAssertCount();
  ASSERT(2 + 2 == 4);
  int after = GetAssertCount();
  ASSERT(after == before + 1);
}

// Run all the registered unit tests.
int main() {
  for (const TestFunction& testFunction : registry) {
    testFunction();
  }
  cout << "All tests passed (" << GetAssertCount() << " assertions in "
       << registry.size() << " test cases)" << endl;
  return 0;
}
