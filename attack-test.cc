#include "attack.h"
#include "board.h"
#include "catch.hpp"
#include "color.h"
#include "fen.h"
#include "std.h"

TEST_CASE("Attack detection: opening position", "[Attack]") {
  const string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  const Board b = FenToBoard(fen);
  REQUIRE(IsSquareUnderAttackByColor(b, Point("e3"), White));
  REQUIRE_FALSE(IsSquareUnderAttackByColor(b, Point("e3"), Black));
  REQUIRE(IsSquareUnderAttackByColor(b, Point("e6"), Black));
  REQUIRE_FALSE(IsSquareUnderAttackByColor(b, Point("e6"), White));
  REQUIRE_FALSE(IsSquareUnderAttackByColor(b, Point("e5"), White));
  REQUIRE_FALSE(IsSquareUnderAttackByColor(b, Point("e5"), Black));
}
