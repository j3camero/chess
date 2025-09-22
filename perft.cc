#include "check.h"
#include "makemove.h"
#include "move.h"
#include "movegen.h"
#include "perft.h"
#include "std.h"

uint64_t Perft(Board& b, int depth) {
  if (depth == 0) {
    return 1;
  }
  uint64_t sum = 0;
  vector<Move> pseudo = GeneratePseudoLegalMoves(b);
  for (const Move& move : pseudo) {
    Irreversible irr = b.irreversible;
    MakeMove(b, move);
    if (!IsOppInCheck(b)) {
      sum += Perft(b, depth - 1);
    }
    UndoMove(b, move, irr);
  }
  return sum;
}

uint64_t PerftWithDebugOutput(Board& b, int depth) {
  if (depth == 0) {
    return 1;
  }
  uint64_t sum = 0;
  vector<Move> pseudo = GeneratePseudoLegalMoves(b);
  for (const Move& move : pseudo) {
    Irreversible irr = b.irreversible;
    MakeMove(b, move);
    if (!IsOppInCheck(b)) {
      uint64_t p = Perft(b, depth - 1);
      cout << move.ToString() << ": " << p << endl;
      sum += p;
    }
    UndoMove(b, move, irr);
  }
  cout << endl << "Nodes searched: " << sum << endl;
  return sum;
}
