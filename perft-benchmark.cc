#include "board.h"
#include "fen.h"
#include "perft.h"
#include "std.h"

int main() {
  string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  Board b = FenToBoard(fen);
  for (int depth = 0; depth < 99; depth++) {
    auto startTime = chrono::high_resolution_clock::now();
    uint64_t p = Perft(b, depth);
    auto endTime = chrono::high_resolution_clock::now();
    auto elapsedTime = endTime - startTime;
    auto ms = chrono::duration_cast<chrono::milliseconds>(elapsedTime).count();
    auto knps = (ms == 0) ? 0 : (p / ms);
    cout << "perft(" << depth << ") = " << p << " - " << ms << " ms - " << knps << " knps" << endl;
    Board original = FenToBoard(fen);
    if (b != original) {
      cout << "Board does not match original. This is bad!" << endl;
    }
  }
  return 0;
}
