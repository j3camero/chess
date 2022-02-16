#include "std.h"

int main(int argc, char **argv) {
  string line;
  while (getline(cin, line)) {
    vector<string> tokens = StringUtil::Split(line);
    if (tokens[0] == "uci") {
      cout << "id name jeffchess " << GIT_VERSION << endl;
      cout << "id author Jeff Cameron jcameron.ca" << endl;
    } else if (tokens[0] == "quit") {
      break;
    }
  }
  return 0;
}
