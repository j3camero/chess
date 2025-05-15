// Unit test framework.
//
// Auto registers unit tests using C++ preprocessor magic.
#ifndef _TEST_H_
#define _TEST_H_

#include "std.h"

#define TEST(name) \
  struct Test##name { \
    Test##name(); \
  } test##name; \
  Test##name::Test##name()

// Assert is defined as a macro. This lets it print out helpful info when it
// fails, like the condition and what line of what file it's on.
#define ASSERT(condition) \
  IncrementAssertCount(); \
  if (!(condition)) { \
    cerr << "Assertion failed: " #condition \
         << " at line " << __LINE__ \
         << " in file " << __FILE__ << endl; \
    abort(); \
  }

#define ASSERT_EXCEPTION(statement) \
  IncrementAssertCount(); \
  try { \
    statement; \
    cerr << "Assertion failed: " #statement \
         << " at line " << __LINE__ \
         << " in file " << __FILE__ << endl; \
    abort(); \
  } catch (...) {}

// Counts the number of calls to ASSERT behind the scenes.
void IncrementAssertCount();

// Returns the number of times that ASSERT has been called.
int GetAssertCount();

// Unit tests.
void TestAssert();

#endif
