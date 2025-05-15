#include "irreversible.h"
#include "test.h"

TEST(BasicIrreversibleStateConstructor) {
  Irreversible i;
  ASSERT(i.castleBits == 0);
  ASSERT(i.enPassantFile == -1);
  ASSERT(i.halfmoveClock == 0);
}

TEST(CastleBits) {
  Irreversible i;
  ASSERT(i.castleBits == 0);
  i.SetWhiteKingCastle();
  ASSERT(i.castleBits == 1);
  i.SetBlackQueenCastle();
  ASSERT(i.castleBits == 9);
  i.ClearWhiteKingCastle();
  ASSERT(i.castleBits == 8);
  i.SetBlackKingCastle();
  ASSERT(i.castleBits == 12);
  i.SetWhiteQueenCastle();
  ASSERT(i.castleBits == 14);
  i.ClearBlackQueenCastle();
  ASSERT(i.castleBits == 6);
  i.ClearWhiteQueenCastle();
  ASSERT(i.castleBits == 4);
  i.ClearBlackKingCastle();
  ASSERT(i.castleBits == 0);
}
