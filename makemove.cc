#include "board.h"
#include "color.h"
#include "irreversible.h"
#include "makemove.h"
#include "move.h"
#include "piece.h"

void MakeMove(Board& b, const Move& m) {
  Color sideToMove = b.turn;
  Piece movingPiece = b.piece[m.from.rank][m.from.file];
  if (m.isPromotion) {
    // Pawn promotion.
    b.piece[m.to.rank][m.to.file] = m.promotionPiece;
  } else {
    // Regular piece moves.
    b.piece[m.to.rank][m.to.file] = movingPiece;
  }
  // Update the colors of the squares.
  b.color[m.to.rank][m.to.file] = sideToMove;
  b.color[m.from.rank][m.from.file] = Empty;
  // Flip the side-to-move.
  b.turn = b.opp;
  b.opp = sideToMove;
  // Increment the moveCount after every black move.
  if (sideToMove == Black) {
    b.moveCount++;
  }
  // Captures reset the halfmoveClock.
  if (m.isCapture) {
    b.irreversible.halfmoveClock = 0;
  }
  // Special handling for pawn moves.
  if (movingPiece == Pawn) {
    // Pawn moves reset halfmoveClock.
    b.irreversible.halfmoveClock = 0;
    // En-passant capture.
    if (m.isCapture && m.to.file == b.irreversible.enPassantFile) {
      b.color[m.from.rank][m.to.file] = Empty;
    }
    // Detect pawn push. Set EP file. This has to go after en-passant capture
    // because it mutates the enPassantFile field.
    if (m.to.rank == m.from.rank + 2 || m.to.rank == m.from.rank - 2) {
      b.irreversible.enPassantFile = m.to.file;
    }
  }
  // Special handling for rook moves.
  else if (movingPiece == Rook) {
    if (sideToMove == White) {
      if (m.from.rank == 0 && m.from.file == 0) {
        b.irreversible.ClearWhiteQueenCastle();
      }
      if (m.from.rank == 0 && m.from.file == 7) {
        b.irreversible.ClearWhiteKingCastle();
      }
    } else {
      if (m.from.rank == 7 && m.from.file == 0) {
        b.irreversible.ClearBlackQueenCastle();
      }
      if (m.from.rank == 7 && m.from.file == 7) {
        b.irreversible.ClearBlackKingCastle();
      }
    }
  }
  // Special handling for king moves.
  else if (movingPiece == King) {
    if (sideToMove == White) {
      b.whiteKingLocation = m.to;
      b.irreversible.ClearWhiteKingCastle();
      b.irreversible.ClearWhiteQueenCastle();
      if (m.from.file == 4 && m.to.file == 6) {
        // King-side castle. Move rook.
        b.color[0][7] = Empty;
        b.color[0][5] = White;
        b.piece[0][5] = Rook;
      } else if (m.from.file == 4 && m.to.file == 2) {
        // Queen-side castle. Move rook.
        b.color[0][0] = Empty;
        b.color[0][3] = White;
        b.piece[0][3] = Rook;
      }
    } else {
      b.blackKingLocation = m.to;
      b.irreversible.ClearBlackKingCastle();
      b.irreversible.ClearBlackQueenCastle();
      if (m.from.file == 4 && m.to.file == 6) {
        // King-side castle. Move rook.
        b.color[7][7] = Empty;
        b.color[7][5] = Black;
        b.piece[7][5] = Rook;
      } else if (m.from.file == 4 && m.to.file == 2) {
        // Queen-side castle. Move rook.
        b.color[7][0] = Empty;
        b.color[7][3] = Black;
        b.piece[7][3] = Rook;
      }
    }
  }
}

void UndoMove(Board& b, const Move& m, const Irreversible i) {

}
