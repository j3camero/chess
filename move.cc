#include "board.h"
#include "move.h"
#include "piece.h"
#include "std.h"

Move::Move(Point from, Point to) : from(from), to(to) {}

Move::Move(const string& s) {
  if (s.length() != 4) {
    throw "Invalid move string format. Must be formatted like e2e4.";
  }
  from = Point(s.substr(0, 2));
  to = Point(s.substr(2));
}

void GenerateKnightMoves(const Board& board, Point from, vector<Move>& moves) {
  Color enemy = InvertColor(board.move);
  Point directions[8] = {
    Point(1, 2), Point(2, 1), Point(2, -1), Point(1, -2),
    Point(-1, -2), Point(-2, -1), Point(-2, 1), Point(-1, 2)
  };
  for (const Point& d : directions) {
    Point to(from.rank + d.rank, from.file + d.file);
    if (to.rank < 0 || to.rank > 7 || to.file < 0 || to.file > 7) {
      // Move is off the board.
      continue;
    }
    Piece p = board.squares[to.rank][to.file];
    Move move(from, to);
    if (p == Empty) {
      moves.push_back(move);
      continue;
    }
    Color attackedPieceColor = PieceColor(p);
    if (attackedPieceColor == enemy) {
      moves.push_back(move);
    }
  }
}

void GenerateLegalMovesFrom(const Board& board,
                            Point from,
                            vector<Move>& moves) {
  Piece piece = board.squares[from.rank][from.file];
  if (piece == Empty) {
    return;
  }
  Color color = PieceColor(piece);
  if (color != board.move) {
    return;
  }
  switch (piece) {
  case BlackKnight:
  case WhiteKnight:
    GenerateKnightMoves(board, from, moves);
    break;
  }
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

bool operator==(const Move& a, const Move& b) {
  return (a.from == b.from) && (a.to == b.to);
}

bool operator!=(const Move& a, const Move& b) {
  return !(a == b);
}
