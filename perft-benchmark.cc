#include "board.h"
#include "fen.h"
#include "perft.h"
#include "std.h"

int main() {
  string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  Board b = FenToBoard(fen);
  for (int depth = 0; depth < 5; depth++) {
    uint64_t p = Perft(b, depth);
    Board original = FenToBoard(fen);
    cout << "perft(" << depth << ") = " << p << endl;
    if (b != original) {
      cout << "Board does not match original. This is bad!" << endl;
    }
  }
  return 0;
}
