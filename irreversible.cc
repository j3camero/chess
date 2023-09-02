#include "irreversible.h"

Irreversible::Irreversible()
  : castleBits(0), enPassantFile(-1), halfmoveClock(0) {}

inline bool Irreversible::WhiteKingCastleAllowed() const {
    return castleBits & 1;
}

inline bool Irreversible::WhiteQueenCastleAllowed() const {
    return castleBits & 2;
}

inline bool Irreversible::BlackKingCastleAllowed() const {
    return castleBits & 4;
}

inline bool Irreversible::BlackQueenCastleAllowed() const {
    return castleBits & 8;
}

inline void Irreversible::SetWhiteKingCastle() {
    castleBits |= 1;
}

inline void Irreversible::SetWhiteQueenCastle() {
    castleBits |= 2;
}

inline void Irreversible::SetBlackKingCastle() {
    castleBits |= 4;
}

inline void Irreversible::SetBlackQueenCastle() {
    castleBits |= 8;
}

inline void Irreversible::ClearWhiteKingCastle() {
    castleBits ^= 254;
}

inline void Irreversible::ClearWhiteQueenCastle() {
    castleBits ^= 253;
}

inline void Irreversible::ClearBlackKingCastle() {
    castleBits ^= 251;
}

inline void Irreversible::ClearBlackQueenCastle() {
    castleBits ^= 247;
}
