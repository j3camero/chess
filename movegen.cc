#include "movegen.h"
#include "piece-moves.h"

// Add the given move to the list if the destination square is available or
// is an enemy piece. Does not check the moving piece or consider check. This
// is a helper function for generating moves that emerged from refactoring.
// Returns true if the destination square is empty.
bool TryMove(const Board& board, Move move, vector<Move>& moves) {
  if (!move.to.IsOnBoard()) {
    return false;
  }
  const Color color = board.color[move.to.rank][move.to.file];
  if (color == Empty) {
    moves.push_back(move);
    return true;
  }
  if (color != board.turn) {
    moves.push_back(move);
  }
  return false;
}

void GenerateKnightMoves(const Board& board, Point from, vector<Move>& moves) {
  for (const Point& k : knightMoves) {
    Point to = from + k;
    Move move(from, to);
    TryMove(board, move, moves);
  }
}

void GenerateKingMoves(const Board& board, Point from, vector<Move>& moves) {
  for (const Point& direction : queenMoves) {
    Point to = from + direction;
    Move move(from, to);
    TryMove(board, move, moves);
  }
}

void GenerateSlidingPieceMoves(const Board& board,
                               Point from,
                               Point to,
                               Point direction,
                               vector<Move>& moves) {
  to += direction;
  Move move(from, to);
  bool keepGoing = TryMove(board, move, moves);
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
  if (color == targetColor) {
    Move move(from, to);
    moves.push_back(move);
    return true;
  }
  return false;
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
  Move move(from, to);
  moves.push_back(move);
}

void GenerateEnPassantCaptures(const Board& board, vector<Move>& moves) {
  if (board.enPassantFile < 0) {
    return;
  }
  const int toRank = board.turn == White ? 2 : 5;
  const int fromRank = board.turn == White ? 3 : 4;
  Point to(toRank, board.enPassantFile);
  if (board.enPassantFile > 0) {
    Point left(fromRank, board.enPassantFile - 1);
    TryEnPassant(board, left, to, moves);
  }
  if (board.enPassantFile < 7) {
    Point right(fromRank, board.enPassantFile + 1);
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

void GenerateCastleMoves(const Board& board, vector<Move>& moves) {
  if (board.turn == White) {
    if (board.whiteKingCastle) {
      
    }
  } else {

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
