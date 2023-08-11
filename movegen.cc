#include "movegen.h"

Point knightMoves[8] = {
  Point(1, 2), Point(2, 1), Point(2, -1), Point(1, -2),
  Point(-1, -2), Point(-2, -1), Point(-2, 1), Point(-1, 2)
};
Point rookMoves[4] = {
  Point(1, 0), Point(0, 1), Point(-1, 0), Point(0, -1)
};
Point bishopMoves[4] = {
  Point(1, 1), Point(-1, 1), Point(1, -1), Point(-1, -1)
};
Point queenMoves[8] = {
  Point(1, 0), Point(0, 1), Point(-1, 0), Point(0, -1),
  Point(1, 1), Point(-1, 1), Point(1, -1), Point(-1, -1)
};

// Add the given move to the list if the destination square is available or
// is an enemy piece. Does not check the moving piece or consider check. This
// is a helper function for generating moves that emerged from refactoring.
// Returns true if the destination square is empty.
bool TryMove(const Board& board, Move move, vector<Move>& moves) {
  if (move.to.rank < 0 || move.to.rank > 7 ||
      move.to.file < 0 || move.to.file > 7) {
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

void GenerateKingMoves(const Board& board, Point from, vector<Move>& moves) {
  for (const Point& direction : queenMoves) {
    Point to = from + direction;
    Move move(from, to);
    TryMove(board, move, moves);
  }
}

void GeneratePawnMoves(const Board& board, Point from, vector<Move>& moves) {

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

vector<Move> GeneratePseudoLegalMoves(const Board& board) {
  vector<Move> moves;
  for (int rank = 0; rank < 8; rank++) {
    for (int file = 0; file < 8; file++) {
      Point from(rank, file);
      GenerateMovesFrom(board, from, moves);
    }
  }
  return moves;
}
