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
