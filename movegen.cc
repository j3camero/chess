#include "attack.h"
#include "board.h"
#include "check.h"
#include "fen.h"
#include "makemove.h"
#include "move.h"
#include "movegen.h"
#include "piece-moves.h"
#include "std.h"

// Add the given move to the list if the destination square is available or
// is an enemy piece. Does not check the moving piece or consider check. This
// is a helper function for generating moves that emerged from refactoring.
// Returns true if the destination square is empty.
bool TryMove(const Board& board, const Point& from, const Point& to, vector<Move>& moves) {
  if (!to.IsOnBoard()) {
    return false;
  }
  const Color color = board.color[to.rank][to.file];
  if (color == Empty) {
    moves.push_back(Move(from, to));
    return true;
  }
  if (color != board.turn) {
    Piece capturedPiece = board.piece[to.rank][to.file];
    moves.push_back(Move(from, to, true, capturedPiece));
  }
  return false;
}

void GenerateKnightMoves(const Board& board, Point from, vector<Move>& moves) {
  for (const Point& k : knightMoves) {
    Point to = from + k;
    TryMove(board, from, to, moves);
  }
}

void GenerateKingMoves(const Board& board, Point from, vector<Move>& moves) {
  for (const Point& direction : queenMoves) {
    Point to = from + direction;
    TryMove(board, from, to, moves);
  }
}

void GenerateSlidingPieceMoves(const Board& board,
                               Point from,
                               Point to,
                               Point direction,
                               vector<Move>& moves) {
  to += direction;
  bool keepGoing = TryMove(board, from, to, moves);
  if (keepGoing) {
    GenerateSlidingPieceMoves(board, from, to, direction, moves);
  }
}

void GenerateRookMoves(const Board& board, Point from, vector<Move>& moves) {
  for (const Point& direction : rookMoves) {
    GenerateSlidingPieceMoves(board, from, from, direction, moves);
  }
}

void GenerateBishopMoves(const Board& board, Point from, vector<Move>& moves) {
  for (const Point& direction : bishopMoves) {
    GenerateSlidingPieceMoves(board, from, from, direction, moves);
  }
}

void GenerateQueenMoves(const Board& board, Point from, vector<Move>& moves) {
  for (const Point& direction : queenMoves) {
    GenerateSlidingPieceMoves(board, from, from, direction, moves);
  }
}

// Helper function for generating pawn moves and captures.
// Does not do any bounds checking. The caller must ensure the destination
// square is within the edges of the board.
// Returns true if the move was valid.
bool TryPawnMove(const Board& board,
                 Point from,
                 Point to,
                 Color targetColor,
                 vector<Move>& moves) {
  const Color color = board.color[to.rank][to.file];
  if (color != targetColor) {
    return false;
  }
  bool isCapture = color != Empty;
  Piece capturedPiece = board.piece[to.rank][to.file];
  int promotionRank = board.turn == White ? 0 : 7;
  if (to.rank == promotionRank) {
    moves.push_back(Move(from, to, isCapture, capturedPiece, true, Queen));
    moves.push_back(Move(from, to, isCapture, capturedPiece, true, Knight));
    moves.push_back(Move(from, to, isCapture, capturedPiece, true, Rook));
    moves.push_back(Move(from, to, isCapture, capturedPiece, true, Bishop));
  } else {
    moves.push_back(Move(from, to, isCapture, capturedPiece));
  }
  return true;
}

void GeneratePawnMoves(const Board& board, Point from, vector<Move>& moves) {
  // Pawns are the only piece for which color/direction matter.
  const int direction = board.turn == White ? -1 : 1;
  // Try right capture.
  if (from.file < 7) {
    Point right = from + Point(direction, 1);
    TryPawnMove(board, from, right, board.opp, moves);
  }
  // Try left capture.
  if (from.file > 0) {
    Point left = from + Point(direction, -1);
    TryPawnMove(board, from, left, board.opp, moves);
  }
  // Try normal pawn move forward.
  Point forward(direction, 0);
  Point to = from + forward;
  bool canMove = TryPawnMove(board, from, to, Empty, moves);
  if (!canMove) {
    return;
  }
  // Try pawn push (move 2 forward).
  int secondRank = board.turn == White ? 6 : 1;
  if (from.rank != secondRank) {
    return;
  }
  Point two = to + forward;
  TryPawnMove(board, from, two, Empty, moves);
}

// Helper function for generating en-passant capture moves for pawns.
// Assumptions:
// (1) The target square (to) is Empty.
// (2) from and to are both on the board.
// (3) Most recent move was an enemy pawn push, as recorded in the en-passant
//     file. The enemy pawn to be captured is found in the expected square.
// Only has to check that the capturing piece is a friendly pawn.
void TryEnPassant(const Board& board,
                  Point from,
                  Point to,
                  vector<Move>& moves) {
  const Color color = board.color[from.rank][from.file];
  if (color != board.turn) {
    return;
  }
  const Piece piece = board.piece[from.rank][from.file];
  if (piece != Pawn) {
    return;
  }
  Move move(from, to, true, Pawn);
  moves.push_back(move);
}

void GenerateEnPassantCaptures(const Board& board, vector<Move>& moves) {
  if (board.irreversible.enPassantFile < 0) {
    return;
  }
  const int toRank = board.turn == White ? 2 : 5;
  const int fromRank = board.turn == White ? 3 : 4;
  Point to(toRank, board.irreversible.enPassantFile);
  if (board.irreversible.enPassantFile > 0) {
    Point left(fromRank, board.irreversible.enPassantFile - 1);
    TryEnPassant(board, left, to, moves);
  }
  if (board.irreversible.enPassantFile < 7) {
    Point right(fromRank, board.irreversible.enPassantFile + 1);
    TryEnPassant(board, right, to, moves);
  }
}

void GenerateMovesFrom(const Board& board, Point from, vector<Move>& moves) {
  const Color color = board.color[from.rank][from.file];
  if (color != board.turn) {
    return;
  }
  const Piece piece = board.piece[from.rank][from.file];
  switch (piece) {
  case Knight:
    GenerateKnightMoves(board, from, moves);
    break;
  case Rook:
    GenerateRookMoves(board, from, moves);
    break;
  case Bishop:
    GenerateBishopMoves(board, from, moves);
    break;
  case Queen:
    GenerateQueenMoves(board, from, moves);
    break;
  case King:
    GenerateKingMoves(board, from, moves);
    break;
  case Pawn:
    GeneratePawnMoves(board, from, moves);
    break;
  }
}

// Generates pseudo-legal castle moves. This function skips checking the
// destination square for check to save calculation time.
void GenerateCastleMoves(const Board& board, vector<Move>& moves) {
  if (board.turn == White) {
    if (!board.irreversible.WhiteKingCastleAllowed() && !board.irreversible.WhiteQueenCastleAllowed()) {
      return;
    }
    bool e1Attacked = IsSquareUnderAttackByColor(board, e1, Black);
    if (e1Attacked) {
      return;
    }
    if (board.irreversible.WhiteKingCastleAllowed() &&
        board.color[7][5] == Empty &&
        board.color[7][6] == Empty &&
        !IsSquareUnderAttackByColor(board, f1, Black) &&
        !IsSquareUnderAttackByColor(board, g1, Black)) {
      moves.push_back(whiteKingCastle);
    }
    if (board.irreversible.WhiteQueenCastleAllowed() &&
        board.color[7][3] == Empty &&
        board.color[7][2] == Empty &&
        board.color[7][1] == Empty &&
        !IsSquareUnderAttackByColor(board, d1, Black) &&
        !IsSquareUnderAttackByColor(board, c1, Black)) {
      moves.push_back(whiteQueenCastle);
    }
  } else {
    if (!board.irreversible.BlackKingCastleAllowed() && !board.irreversible.BlackQueenCastleAllowed()) {
      return;
    }
    bool e8Attacked = IsSquareUnderAttackByColor(board, e8, White);
    if (e8Attacked) {
      return;
    }
    if (board.irreversible.BlackKingCastleAllowed() &&
        board.color[0][5] == Empty &&
        board.color[0][6] == Empty &&
        !IsSquareUnderAttackByColor(board, f8, White) &&
        !IsSquareUnderAttackByColor(board, g8, White)) {
      moves.push_back(blackKingCastle);
    }
    if (board.irreversible.BlackQueenCastleAllowed() &&
        board.color[0][3] == Empty &&
        board.color[0][2] == Empty &&
        board.color[0][1] == Empty &&
        !IsSquareUnderAttackByColor(board, d8, White) &&
        !IsSquareUnderAttackByColor(board, c8, White)) {
      moves.push_back(blackQueenCastle);
    }
  }
}

vector<Move> GeneratePseudoLegalMoves(const Board& board) {
  vector<Move> moves;
  for (int rank = 0; rank < 8; rank++) {
    for (int file = 0; file < 8; file++) {
      Point from(rank, file);
      GenerateMovesFrom(board, from, moves);
    }
  }
  GenerateEnPassantCaptures(board, moves);
  GenerateCastleMoves(board, moves);
  return moves;
}

vector<Move> GenerateLegalMoves(Board& board) {
  vector<Move> pseudo = GeneratePseudoLegalMoves(board);
  vector<Move> legal;
  for (const Move& move : pseudo) {
    Irreversible irr = board.irreversible;
    MakeMove(board, move);
    if (!IsOppInCheck(board)) {
      legal.push_back(move);
    }
    UndoMove(board, move, irr);
  }
  return legal;
}
