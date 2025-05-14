// Helper functions for unit testing.
#ifndef _ASSERT_H_
#define _ASSERT_H_

#include "std.h"

// Counts the number of calls to ASSERT behind the scenes.
void IncrementAssertCount();

// Returns the number of times that ASSERT has been called.
int GetAssertCount();

// Unit tests.
void TestAssert();

// Assert is defined as a macro. This lets it print out helpful info when it
// fails, like the condition and what line of what file it's on.
#define ASSERT(condition) \
  do { \
    if (!(condition)) { \
      std::cerr << "Assertion failed: " #condition << " at line " << __LINE__ << " in file " << __FILE__ << std::endl; \
      std::abort(); \
    } \
    IncrementAssertCount(); \
  } while (0)

#endif
