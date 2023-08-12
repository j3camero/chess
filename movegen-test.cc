#include "board.h"
#include "catch.hpp"
#include "fen.h"
#include "move.h"
#include "movegen.h"
#include "std.h"

TEST_CASE("Move generation: opening position", "[Move]") {
  const string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  const Board b = FenToBoard(fen);
  const vector<Move> moves = GeneratePseudoLegalMoves(b);
  const vector<string> actual = MovesToStrings(moves);
  // 20 possible moves from the opening position.
  const vector<string> expected = { "a2a3", "a2a4", "b1a3", "b1c3",
                                    "b2b3", "b2b4", "c2c3", "c2c4",
                                    "d2d3", "d2d4", "e2e3", "e2e4",
                                    "f2f3", "f2f4", "g1f3", "g1h3",
                                    "g2g3", "g2g4", "h2h3", "h2h4" };
  REQUIRE(actual == expected);
}
