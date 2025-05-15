// Unit test framework.
//
// Auto registers unit tests using C++ preprocessor magic.
#ifndef _TEST_H_
#define _TEST_H_

#include "std.h"

#define TEST(name) \
  void test_function_##name(); \
  struct RegisterTest##name { \
    RegisterTest##name() { \
      RegisterTest(test_function_##name); \
    } \
  }; \
  static RegisterTest##name register_test_##name; \
  void test_function_##name()

// Assert is defined as a macro. This lets it print out helpful info when it
// fails, like what line of what file it's on.
#define ASSERT(condition) \
  IncrementAssertCount(); \
  if (!(condition)) { \
    FAIL(condition); \
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
    FAIL(statement); \
  } catch (...) {}

// When a unit test fails, print out which file and line.
#define FAIL(message) \
  cerr << "Assertion failed: " #message \
       << " at line " << __LINE__ \
       << " in file " << __FILE__ << endl; \
  abort();

// Each unit test is a simple function with no parameters that returns nothing.
typedef void (*TestFunction)();

// Registers a unit test. Do not call this function. Use the TEST macro instead.
void RegisterTest(TestFunction function);

// Counts how many times ASSERT gets called behind the scenes.
void IncrementAssertCount();

// Returns the number of times that ASSERT has been called.
int GetAssertCount();

#endif
