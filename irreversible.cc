#include "assert.h"
#include "irreversible.h"

Irreversible::Irreversible()
  : castleBits(0), enPassantFile(-1), halfmoveClock(0) {}

bool Irreversible::WhiteKingCastleAllowed() const {
    return castleBits & 1;
}

bool Irreversible::WhiteQueenCastleAllowed() const {
    return castleBits & 2;
}

bool Irreversible::BlackKingCastleAllowed() const {
    return castleBits & 4;
}

bool Irreversible::BlackQueenCastleAllowed() const {
    return castleBits & 8;
}

void Irreversible::SetWhiteKingCastle() {
    castleBits |= 1;
}

void Irreversible::SetWhiteQueenCastle() {
    castleBits |= 2;
}

void Irreversible::SetBlackKingCastle() {
    castleBits |= 4;
}

void Irreversible::SetBlackQueenCastle() {
    castleBits |= 8;
}

void Irreversible::ClearWhiteKingCastle() {
    castleBits &= 254;
}

void Irreversible::ClearWhiteQueenCastle() {
    castleBits &= 253;
}

void Irreversible::ClearBlackKingCastle() {
    castleBits &= 251;
}

void Irreversible::ClearBlackQueenCastle() {
    castleBits &= 247;
}

void TestBasicIrreversibleStateConstructor() {
  Irreversible i;
  ASSERT(i.castleBits == 0);
  ASSERT(i.enPassantFile == -1);
  ASSERT(i.halfmoveClock == 0);
}

void TestCastleBits() {
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

void TestIrreversible() {
  TestBasicIrreversibleStateConstructor();
  TestCastleBits();
}
