#include "std.h"
#include "string-util.h"

vector<string> StringUtil::Split(const string& s, char delim) {
  vector<string> tokens;
  string token;
  for (const char& c : s) {
    if (c == delim) {
      tokens.push_back(token);
      token.clear();
    } else {
      token += c;
    }
  }
  tokens.push_back(token);
  return tokens;
}
