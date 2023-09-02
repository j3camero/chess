#include "catch.hpp"
#include "irreversible.h"
#include "std.h"

TEST_CASE("Basic irreversible state constructor", "[Irreversible]") {
  Irreversible i;
  REQUIRE(i.castleBits == 0);
  REQUIRE(i.enPassantFile == -1);
  REQUIRE(i.halfmoveClock == 0);
}

TEST_CASE("Castle bits", "[Irreversible]") {
  Irreversible i;
  REQUIRE(i.castleBits == 0);
  i.SetWhiteKingCastle();
  REQUIRE(i.castleBits == 1);
  i.SetBlackQueenCastle();
  REQUIRE(i.castleBits == 9);
  i.ClearWhiteKingCastle();
  REQUIRE(i.castleBits == 8);
  i.SetBlackKingCastle();
  REQUIRE(i.castleBits == 12);
  i.SetWhiteQueenCastle();
  REQUIRE(i.castleBits == 14);
  i.ClearBlackQueenCastle();
  REQUIRE(i.castleBits == 6);
  i.ClearWhiteQueenCastle();
  REQUIRE(i.castleBits == 4);
  i.ClearBlackKingCastle();
  REQUIRE(i.castleBits == 0);
}
