#ifndef _STRING_UTIL_H_
#define _STRING_UTIL_H_

#include "std.h"

// Helper functions for C++ strings.
class StringUtil {
 public:
  // Split s into tokens delimited by delim.
  static vector<string> Split(const string& s, char delim = ' ');
};

#endif
