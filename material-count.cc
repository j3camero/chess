#include "board.h"
#include "fen.h"
#include "makemove.h"
#include "movegen.h"
#include "std.h"
#include "string-util.h"

int PieceValue(Piece piece) {
  switch (piece) {
    case Pawn:
      return 1;
    case Knight:
      return 3;
    case Bishop:
      return 3;
    case Rook:
      return 5;
    case Queen:
      return 9;
    case King:
      return 0;
    default:
      return 0;
  }
}

int MaterialCount(const Board& b) {
  int count = 0;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      Color color = b.color[i][j];
      if (color == White) {
        count += PieceValue(b.piece[i][j]);
      } else if (color == Black) {
        count -= PieceValue(b.piece[i][j]);
      }
    }
  }
  if (b.turn == White) {
    return count;
  } else {
    return -count;
  }
}
