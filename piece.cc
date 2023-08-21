#include "color.h"
#include "piece.h"
#include "std.h"

char PieceToChar(Color c, Piece p) {
  switch (c) {
  case Empty:
    return ' ';
  case White:
    switch (p) {
    case Pawn:
      return 'P';
    case Knight:
      return 'N';
    case Bishop:
      return 'B';
    case Rook:
      return 'R';
    case Queen:
      return 'Q';
    case King:
      return 'K';
    }
  case Black:
    switch (p) {
    case Pawn:
      return 'p';
    case Knight:
      return 'n';
    case Bishop:
      return 'b';
    case Rook:
      return 'r';
    case Queen:
      return 'q';
    case King:
      return 'k';
    }
  }
  // Should never get here.
  throw "Invalid chess piece";
}

void CharToPiece(char c, Color& color, Piece& piece) {
  switch (c) {
  case ' ':
    color = Empty;
    piece = Pawn;
    return;
  case 'P':
    color = White;
    piece = Pawn;
    return;
  case 'N':
    color = White;
    piece = Knight;
    return;
  case 'B':
    color = White;
    piece = Bishop;
    return;
  case 'R':
    color = White;
    piece = Rook;
    return;
  case 'Q':
    color = White;
    piece = Queen;
    return;
  case 'K':
    color = White;
    piece = King;
    return;
  case 'p':
    color = Black;
    piece = Pawn;
    return;
  case 'n':
    color = Black;
    piece = Knight;
    return;
  case 'b':
    color = Black;
    piece = Bishop;
    return;
  case 'r':
    color = Black;
    piece = Rook;
    return;
  case 'q':
    color = Black;
    piece = Queen;
    return;
  case 'k':
    color = Black;
    piece = King;
    return;
  default:
    string exception = "Invalid character for chess piece: ";
    exception += c;
    throw exception;
  }
}
