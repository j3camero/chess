#include "board.h"
#include "move.h"
#include "piece.h"
#include "std.h"

Move::Move(Point from, Point to) : from(from), to(to) {}

void GenerateKnightMoves(const Board& board, Point from, vector<Move>& moves) {
  Color enemy = InvertColor(board.move);
  Point directions[8] = {
    Point(1, 2), Point(2, 1), Point(2, -1), Point(1, -2),
    Point(-1, -2), Point(-2, -1), Point(-2, 1), Point(-1, 2)
  };
  for (const Point& d : directions) {
    Point to(from.rank + d.rank, from.file + d.file);
    Piece p = board.squares[to.rank][to.file];
    Move move(from, to);
    if (p == Empty || PieceColor(p) == enemy) {
      moves.push_back(move);
    }
  }
}

void GenerateLegalMovesFrom(const Board& board,
                            Point from,
                            vector<Move>& moves) {
  // Generate pawn moves/captures.
  GenerateKnightMoves(board, from, moves);
  // Rook.
  // Bishop.
  // Queen.
  // King.
}

vector<Move> GenerateLegalMoves(const Board& board) {
  vector<Move> moves;
  for (int rank = 0; rank < 8; rank++) {
    for (int file = 0; file < 8; file++) {
      Point from(rank, file);
      GenerateLegalMovesFrom(board, from, moves);
    }
  }
  return moves;
}
