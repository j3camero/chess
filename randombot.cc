#include "std.h"
#include "string-util.h"

// Command is "go". Output a randomly chosen legal move.
void Go(const string& command) {
  cout << "bestmove e2e4" << endl;
}

// Command is "isready". Answer with "readyok".
void IsReady(const string& command) {
  cout << "readyok" << endl;
}

// Command is "position". Set up a board position.
void Position(const string& command) {
  // startpos moves || fen
}

// Command is "quit". Exit the program.
void Quit(const string& command) {
  exit(0);
}

// Command is "uci". Print basic info about this chess engine.
void Uci(const string& command) {
  cout << "id name randombot " << GIT_VERSION << endl;
  cout << "id author Jeff Cameron jcameron.ca" << endl;
}

// Command is "ucinewgame". Reset the board.
void UciNewGame(const string& command) {
  // Reset the board here.
  cout << "isready" << endl;
}

// UCI commands are registered in this map.
typedef void (*UciCommand)(const string& command);
map<string, UciCommand> commands;

void Dispatch(const string& line) {
    vector<string> tokens = StringUtil::Split(line);
    if (tokens.size() == 0) {
      return;
    }
    const string command = tokens[0];
    if (commands.count(command) == 0) {
      // Unknown command. As per the UCI protocol, ignore it.
      return;
    }
    const UciCommand handler = commands[command];
    handler(line);
}

int main(int argc, char **argv) {
  // Register UCI commands.
  commands["exit"] = Quit;
  commands["isready"] = IsReady;
  commands["quit"] = Quit;
  commands["uci"] = Uci;
  // Process the input line-by-line.
  string line;
  while (getline(cin, line)) {
    Dispatch(line);
  }
  return 0;
}
