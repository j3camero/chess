#include "catch.hpp"
#include "irreversible.h"

TEST_CASE("Basic irreversible state constructor", "[Irreversible]") {
  Irreversible i;
  REQUIRE(i.castleBits == 0);
  REQUIRE(i.enPassantFile == -1);
  REQUIRE(i.halfmoveClock == 0);
}
