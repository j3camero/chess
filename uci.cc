#include <iostream>
#include <string>

using namespace std;

int main(int argc, char **argv) {
  string line;
  while (getline(cin, line)) {
    if (line == "uci") {
      cout << "id name jeffchess " << GIT_VERSION << endl;
      cout << "id author Jeff Cameron jcameron.ca" << endl;
    } else if (line == "quit") {
      break;
    }
  }
  return 0;
}
