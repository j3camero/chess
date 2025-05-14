#ifndef _IRREVERSIBLE_H_
#define _IRREVERSIBLE_H_

// Represents those aspects of a chess board position state that are not
// incrementally updateable. In other words, irreversible. These fields are
// grouped together into one struct that is kept small enough that it can be
// copied and restored in a single machine instruction. This makes MakeMove()
// and UnmakeMove() efficient.
struct Irreversible {
  // Basic constructor.
  Irreversible();

  // Getter functions for castle bits.
  bool WhiteKingCastleAllowed() const;
  bool WhiteQueenCastleAllowed() const;
  bool BlackKingCastleAllowed() const;
  bool BlackQueenCastleAllowed() const;

  // Setter functions for castle bits.
  void SetWhiteKingCastle();
  void SetWhiteQueenCastle();
  void SetBlackKingCastle();
  void SetBlackQueenCastle();
  void ClearWhiteKingCastle();
  void ClearWhiteQueenCastle();
  void ClearBlackKingCastle();
  void ClearBlackQueenCastle();

  // Castling availability.
  // Bit 0 - Mask 1 - White King Castle
  // Bit 1 - Mask 2 - White Queen Castle
  // Bit 2 - Mask 4 - Black King Castle
  // Bit 3 - Mask 8 - Black Queen Castle
  char castleBits;

  // En-passant target file. -1 if no en-passant capture is available.
  char enPassantFile;

  // Halfmove clock for the fifty-move rule.
  unsigned char halfmoveClock;
};

// Unit tests.
void TestIrreversible();

#endif
