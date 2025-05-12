#include "assert.h"

int assertCount = 0;

void SetAssertCount(int newCount) {
  assertCount = newCount;
}

int GetAssertCount() {
    return assertCount;
}

void IncrementAssertCount() {
  assertCount++;
}

void TestAssert() {
  int before = GetAssertCount();
  ASSERT(2 + 2 == 4);
  int after = GetAssertCount();
  ASSERT(after == before + 1);
}
