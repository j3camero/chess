#include "board.h"
#include "catch.hpp"
#include "fen.h"
#include "move.h"
#include "movegen.h"
#include "std.h"

TEST_CASE("MovesToStrings", "[Move]") {
  const vector<Move> moves = { Move("b1a3"), Move("g8h6") };
  const vector<string> actual = MovesToStrings(moves);
  const vector<string> expected = {"b1a3", "g8h6"};
  REQUIRE(actual == expected);
}

TEST_CASE("Move generation: opening position", "[Move]") {
  const string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  const Board b = FenToBoard(fen);
  const vector<Move> moves = GeneratePseudoLegalMoves(b);
  const vector<string> actual = MovesToStrings(moves);
  const vector<string> expected = {"b1a3", "b1c3", "g1f3", "g1h3"};
  REQUIRE(actual == expected);
}
