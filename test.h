// Unit test framework.
//
// Auto registers unit tests using C++ preprocessor magic.
#ifndef _TEST_H_
#define _TEST_H_

#include "std.h"

// Unit tests run before main(). Methods declared with the RUN_BEFORE_MAIN
// or TEST return type are in effect auto-registered to run before main().
#define RUN_BEFORE_MAIN void __attribute__ ((constructor))
#define TEST RUN_BEFORE_MAIN

// Assert is defined as a macro. This lets it print out helpful info when it
// fails, like what line of what file it's on.
#define ASSERT(condition) \
  IncrementAssertCount(); \
  if (!(condition)) { \
    cerr << "Assertion failed: " #condition \
         << " at line " << __LINE__ \
         << " in file " << __FILE__ << endl; \
    abort(); \
  }

// Accepts a statement or code block and asserts that it must throw an
// exception. If the statement or code block finishes executing without
// throwing an exception, the assert fails. If it does throw an exception,
// the assert passes. The assert catches the exception internally so it does
// not propagate or cause the program execution to crash.
#define ASSERT_EXCEPTION(statement) \
  IncrementAssertCount(); \
  try { \
    statement; \
    cerr << "Assertion failed: " #statement \
         << " at line " << __LINE__ \
         << " in file " << __FILE__ << endl; \
    abort(); \
  } catch (...) {}

// Counts how many times ASSERT gets called behind the scenes.
void IncrementAssertCount();

// Returns the number of times that ASSERT has been called.
int GetAssertCount();

#endif
