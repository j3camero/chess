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
  Color sideThatMoved = b.opp;
  Color sideThatDidNotMove = b.turn;
  Piece movedPiece = m.isPromotion ? Pawn : b.piece[m.to.rank][m.to.file];
  // Move the piece back.
  b.piece[m.from.rank][m.from.file] = movedPiece;
  // Update the colors of the squares.
  b.color[m.from.rank][m.from.file] = sideThatMoved;
  b.color[m.to.rank][m.to.file] = Empty;
  // Flip the side-to-move.
  b.opp = sideThatDidNotMove;
  b.turn = sideThatMoved;
  // Undo irreversible state by overwriting it.
  b.irreversible = i;
  // Decrement the moveCount when undoing a black move.
  if (sideThatMoved == Black) {
    b.moveCount--;
  }
  // Undo capture move. Put the enemy piece back where it was.
  if (m.isCapture) {
    int f = m.to.file;
    int r = m.to.rank;
    if (movedPiece == Pawn && f == i.enPassantFile) {
      // En-passant.
      r = m.from.rank;
    }
    b.piece[r][f] = m.capturedPiece;
    b.color[r][f] = sideThatDidNotMove;
  }
  // Special handling for king moves.
  if (movedPiece == King) {
    if (sideThatMoved == White) {
      b.whiteKingLocation = m.from;
    } else {
      b.blackKingLocation = m.from;
    }
    int r = m.from.rank;
    if (m.from.file == 4 && m.to.file == 6) {
      // King-side castle. Move rook.
      b.color[r][7] = sideThatMoved;
      b.color[r][5] = Empty;
      b.piece[r][7] = Rook;
    } else if (m.from.file == 4 && m.to.file == 2) {
      // Queen-side castle. Move rook.
      b.color[r][0] = sideThatMoved;
      b.color[r][3] = Empty;
      b.piece[r][0] = Rook;
    }
  }
}
