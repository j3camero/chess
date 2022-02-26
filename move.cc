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

string Move::ToString() const {
  return from.ToString() + to.ToString();
}

bool Move::operator==(const Move& other) const {
  return (this->from == other.from) && (this->to == other.to);
}

bool Move::operator!=(const Move& other) const {
  return !(*this == other);
}

vector<string> MovesToStrings(const vector<Move>& moves) {
  vector<string> moveStrings;
  for (const Move& move : moves) {
    const string s = move.ToString();
    moveStrings.push_back(s);
  }
  sort(moveStrings.begin(), moveStrings.end());
  return moveStrings;
}

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
  const Piece piece = board.squares[move.to.rank][move.to.file];
  if (piece == Empty) {
    moves.push_back(move);
    return true;
  }
  if (PieceColor(piece) != board.move) {
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
  case BlackRook:
  case WhiteRook:
    GenerateRookMoves(board, from, moves);
    break;
  case BlackBishop:
  case WhiteBishop:
    GenerateBishopMoves(board, from, moves);
    break;
  case BlackQueen:
  case WhiteQueen:
    GenerateQueenMoves(board, from, moves);
    break;
  case BlackKing:
  case WhiteKing:
    GenerateKingMoves(board, from, moves);
    break;
  case BlackPawn:
  case WhitePawn:
    GeneratePawnMoves(board, from, moves);
    break;
  default:
    // Empty square. Skip it.
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
