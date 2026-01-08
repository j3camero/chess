#include "check.h"
#include "fen.h"
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
  Board original = b;
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
    if (b != original) {
      cout << "WARNING: UndoMove error caused by move " << move.ToString() << endl;
    }
  }
  cout << endl << "Nodes searched: " << sum << endl;
  return sum;
}

uint64_t PerftWithMemoryRecursive(
  Board& b,
  int depth,
  vector<unordered_map<string,uint64_t>>& cache) {
  if (depth == 0) {
    return 1;
  }
  string fen;
  const int minCacheDepth = 3;
  if (depth >= minCacheDepth) {
    while ((int)cache.size() <= depth) {
      cache.push_back(unordered_map<string,uint64_t>());
    }
    fen = BoardToFen(b);
    auto c = cache[depth];
    auto i = c.find(fen);
    if (i != c.end()) {
      // Cache hit.
      uint64_t value = i->second;
      return value;
    }
  }
  uint64_t sum = 0;
  vector<Move> pseudo = GeneratePseudoLegalMoves(b);
  for (const Move& move : pseudo) {
    Irreversible irr = b.irreversible;
    MakeMove(b, move);
    if (!IsOppInCheck(b)) {
      sum += PerftWithMemoryRecursive(b, depth - 1, cache);
    }
    UndoMove(b, move, irr);
  }
  if (depth >= minCacheDepth) {
    cache[depth][fen] = sum;
  }
  return sum;
}

uint64_t PerftWithMemory(Board& b, int depth) {
  vector<unordered_map<string,uint64_t>> cache;
  uint64_t p = PerftWithMemoryRecursive(b, depth, cache);
  // cout << "CACHE DUMP AFTER PERFT " << depth << ":" << endl;
  // for (int i = 0; i < (int)cache.size(); i++) {
  //   cout << i << " : " << cache[i].size() << endl;
  // }
  return p;
}

bool FindUndoMoveInconsistencies(Board& b, int depth) {
  if (depth == 0) {
    return false;
  }
  Board original = b;
  vector<Move> pseudo = GeneratePseudoLegalMoves(b);
  for (const Move& move : pseudo) {
    Irreversible irr = b.irreversible;
    MakeMove(b, move);
    if (!IsOppInCheck(b)) {
      bool found = FindUndoMoveInconsistencies(b, depth - 1);
      if (found) {
        return true;
      }
    }
    UndoMove(b, move, irr);
    if (b != original) {
      cout << "WARNING: UndoMove error. Original position and resulting position:" << endl
           << BoardToFen(original) << endl
           << BoardToFen(b) << endl
           << "Move: " << move.ToString() << endl;
      MakeMove(original, move);
      cout << "Position after move:" << endl << BoardToFen(original) << endl;
      return true;
    }
  }
  return false;
}
