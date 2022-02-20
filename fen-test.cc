#include "catch.hpp"
#include "board.h"
#include "fen.h"
#include "piece.h"

TEST_CASE("Default constructor", "[Board]") {
  const string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  Board b = FenToBoard(fen);
  REQUIRE(b.squares[0][0] == BlackRook);
}
