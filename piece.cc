#include "piece.h"
#include "std.h"

Color PieceColor(Piece p) {
  switch (p) {
  case WhitePawn:
  case WhiteKnight:
  case WhiteBishop:
  case WhiteRook:
  case WhiteQueen:
  case WhiteKing:
    return White;
  case BlackPawn:
  case BlackKnight:
  case BlackBishop:
  case BlackRook:
  case BlackQueen:
  case BlackKing:
    return Black;
  default:
    throw "Empty piece has no color.";
  }
}

char PieceToChar(Piece p) {
  switch (p) {
  case WhitePawn:
    return 'P';
  case WhiteKnight:
    return 'N';
  case WhiteBishop:
    return 'B';
  case WhiteRook:
    return 'R';
  case WhiteQueen:
    return 'Q';
  case WhiteKing:
    return 'K';
  case BlackPawn:
    return 'p';
  case BlackKnight:
    return 'n';
  case BlackBishop:
    return 'b';
  case BlackRook:
    return 'r';
  case BlackQueen:
    return 'q';
  case BlackKing:
    return 'k';
  case Empty:
    return ' ';
  }
}

Piece CharToPiece(char c) {
  switch (c) {
  case 'P':
    return WhitePawn;
  case 'N':
    return WhiteKnight;
  case 'B':
    return WhiteBishop;
  case 'R':
    return WhiteRook;
  case 'Q':
    return WhiteQueen;
  case 'K':
    return WhiteKing;
  case 'p':
    return BlackPawn;
  case 'n':
    return BlackKnight;
  case 'b':
    return BlackBishop;
  case 'r':
    return BlackRook;
  case 'q':
    return BlackQueen;
  case 'k':
    return BlackKing;
  default:
    string exception = "Invalid character for chess piece: ";
    exception += c;
    throw exception;
  }
}
