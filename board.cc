#include "board.h"

Board::Board() :
  squares {
    {BlackRook, BlackKnight, BlackBishop, BlackQueen,
     BlackKing, BlackBishop, BlackKnight, BlackRook},
    {BlackPawn, BlackPawn, BlackPawn, BlackPawn,
     BlackPawn, BlackPawn, BlackPawn, BlackPawn},
    {Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty},
    {Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty},
    {Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty},
    {Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty},
    {WhitePawn, WhitePawn, WhitePawn, WhitePawn,
     WhitePawn, WhitePawn, WhitePawn, WhitePawn},
    {WhiteRook, WhiteKnight, WhiteBishop, WhiteQueen,
     WhiteKing, WhiteBishop, WhiteKnight, WhiteRook}
  }
{

}

Board::Board(const string& fen) {

}
