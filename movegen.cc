#include "attack.h"
#include "board.h"
#include "check.h"
#include "fen.h"
#include "move.h"
#include "movegen.h"
#include "piece-moves.h"
#include "std.h"
#include "test.h"

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
    if (board.irreversible.WhiteKingCastleAllowed()) {
      if (board.color[7][5] == Empty && board.color[7][6] == Empty) {
        bool f1Attacked = IsSquareUnderAttackByColor(board, f1, Black);
        if (!f1Attacked) {
          moves.push_back(whiteKingCastle);
        }
      }
    }
    if (board.irreversible.WhiteQueenCastleAllowed()) {
      if (board.color[7][3] == Empty && board.color[7][2] == Empty) {
        bool d1Attacked = IsSquareUnderAttackByColor(board, d1, Black);
        if (!d1Attacked) {
          moves.push_back(whiteQueenCastle);
        }
      }
    }
  } else {
    if (!board.irreversible.BlackKingCastleAllowed() && !board.irreversible.BlackQueenCastleAllowed()) {
      return;
    }
    bool e8Attacked = IsSquareUnderAttackByColor(board, e8, White);
    if (e8Attacked) {
      return;
    }
    if (board.irreversible.BlackKingCastleAllowed()) {
      if (board.color[0][5] == Empty && board.color[0][6] == Empty) {
        bool f8Attacked = IsSquareUnderAttackByColor(board, f8, White);
        if (!f8Attacked) {
          moves.push_back(blackKingCastle);
        }
      }
    }
    if (board.irreversible.BlackQueenCastleAllowed()) {
      if (board.color[0][3] == Empty && board.color[0][2] == Empty) {
        bool d8Attacked = IsSquareUnderAttackByColor(board, d8, White);
        if (!d8Attacked) {
          moves.push_back(blackQueenCastle);
        }
      }
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

vector<Move> GenerateLegalMoves(const Board& board) {
  vector<Move> pseudo = GeneratePseudoLegalMoves(board);
  vector<Move> legal;
  for (const Move& move : pseudo) {
    // Makemove
    // Check for opp in check
    legal.push_back(move);
    // Unmakemove
  }
  return legal;
}

// Helper function for finding a move in a list of moves.
bool HasMove(const vector<Move>& v, const Move& m) {
  for (const Move& x : v) {
    if (x == m) {
      return true;
    }
  }
  return false;
}

TEST(MovegenOpeningPosition) {
  const string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  const Board b = FenToBoard(fen);
  const vector<Move> moves = GeneratePseudoLegalMoves(b);
  const vector<string> actual = MovesToStrings(moves);
  // 20 possible moves from the opening position.
  const vector<string> expected = { "a2a3", "a2a4", "b1a3", "b1c3",
                                    "b2b3", "b2b4", "c2c3", "c2c4",
                                    "d2d3", "d2d4", "e2e3", "e2e4",
                                    "f2f3", "f2f4", "g1f3", "g1h3",
                                    "g2g3", "g2g4", "h2h3", "h2h4" };
  ASSERT(actual == expected);
}

TEST(MovegenWhitePawnPromotionWithoutCapture) {
  const string fen = "8/4P3/8/8/8/8/8/8 w - - 0 1";
  const Board b = FenToBoard(fen);
  const vector<Move> moves = GeneratePseudoLegalMoves(b);
  const vector<string> actual = MovesToStrings(moves);
  // 20 possible moves from the opening position.
  const vector<string> expected = { "e7e8b", "e7e8n", "e7e8q", "e7e8r" };
  ASSERT(actual == expected);
}

TEST(MovegenWhitePawnPromotionWithCapture) {
  const string fen = "3qkb2/4P3/8/8/8/8/8/8 w - - 0 1";
  const Board b = FenToBoard(fen);
  const vector<Move> moves = GeneratePseudoLegalMoves(b);
  const vector<string> actual = MovesToStrings(moves);
  // 20 possible moves from the opening position.
  const vector<string> expected = { "e7d8b", "e7d8n", "e7d8q", "e7d8r",
                                    "e7f8b", "e7f8n", "e7f8q", "e7f8r" };
  ASSERT(actual == expected);
}

TEST(MovegenBlackPawnPromotionWithoutCapture) {
  const string fen = "8/8/8/8/8/8/2p5/8 b - - 0 1";
  const Board b = FenToBoard(fen);
  const vector<Move> moves = GeneratePseudoLegalMoves(b);
  const vector<string> actual = MovesToStrings(moves);
  // 20 possible moves from the opening position.
  const vector<string> expected = { "c2c1b", "c2c1n", "c2c1q", "c2c1r" };
  ASSERT(actual == expected);
}

TEST(MovegenBlackPawnPromotionWithCapture) {
  const string fen = "8/8/8/8/8/8/6p1/5Q2 b - - 0 1";
  const Board b = FenToBoard(fen);
  const vector<Move> moves = GeneratePseudoLegalMoves(b);
  const vector<string> actual = MovesToStrings(moves);
  // 20 possible moves from the opening position.
  const vector<string> expected = { "g2f1b", "g2f1n", "g2f1q", "g2f1r",
                                    "g2g1b", "g2g1n", "g2g1q", "g2g1r" };
  ASSERT(actual == expected);
}

TEST(MovegenSlidingPieceCapture) {
  const string fen = "8/8/8/1R3n2/8/8/8/8 w - - 0 1";
  const Board b = FenToBoard(fen);
  const vector<Move> moves = GeneratePseudoLegalMoves(b);
  const vector<string> actual = MovesToStrings(moves);
  // 20 possible moves from the opening position.
  const vector<string> expected = { "b5a5", "b5b1", "b5b2", "b5b3",
                                    "b5b4", "b5b6", "b5b7", "b5b8",
                                    "b5c5", "b5d5", "b5e5", "b5f5" };
  ASSERT(actual == expected);
  // Check capture b5f5 properly marked as a capture move.
  ASSERT(HasMove(moves, Move("b5f5", true, Knight)));
  // Does not contain non-capture b5f5.
  ASSERT(!HasMove(moves, Move("b5f5")));
  // Check capture b5f5 captures the right piece type, knight.
  ASSERT(!HasMove(moves, Move("b5f5", true, Bishop)));
  // Check one of the non-capture moves to make sure it isn't a capture.
  ASSERT(HasMove(moves, Move("b5c5")));
  ASSERT(!HasMove(moves, Move("b5c5", true, Knight)));
}

TEST(MovegenWhiteCastleWithAllOptionsOpen) {
  const string fen = "r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1";
  const Board b = FenToBoard(fen);
  const vector<Move> moves = GeneratePseudoLegalMoves(b);
  ASSERT(moves.size() == 26);
  ASSERT(HasMove(moves, whiteKingCastle));
  ASSERT(HasMove(moves, whiteQueenCastle));
  ASSERT(!HasMove(moves, blackKingCastle));
  ASSERT(!HasMove(moves, blackQueenCastle));
}

TEST(MovegenBlackCastleWithAllOptionsOpen) {
  const string fen = "r3k2r/8/8/8/8/8/8/R3K2R b KQkq - 0 1";
  const Board b = FenToBoard(fen);
  const vector<Move> moves = GeneratePseudoLegalMoves(b);
  ASSERT(moves.size() == 26);
  ASSERT(HasMove(moves, blackKingCastle));
  ASSERT(HasMove(moves, blackQueenCastle));
  ASSERT(!HasMove(moves, whiteKingCastle));
  ASSERT(!HasMove(moves, whiteQueenCastle));
}

TEST(MovegenWhiteCastleBlackedByFlags) {
  const string fen = "r3k2r/8/8/8/8/8/8/R3K2R w - - 0 1";
  const Board b = FenToBoard(fen);
  const vector<Move> moves = GeneratePseudoLegalMoves(b);
  ASSERT(!HasMove(moves, whiteKingCastle));
  ASSERT(!HasMove(moves, whiteQueenCastle));
}

TEST(MovegenBlackCastleBlockedByFlags) {
  const string fen = "r3k2r/8/8/8/8/8/8/R3K2R b - - 0 1";
  const Board b = FenToBoard(fen);
  const vector<Move> moves = GeneratePseudoLegalMoves(b);
  ASSERT(!HasMove(moves, blackKingCastle));
  ASSERT(!HasMove(moves, blackQueenCastle));
}

TEST(MovegenWhiteCastleDifferingFlags) {
  const string fen = "r3k2r/8/8/8/8/8/8/R3K2R w Q - 0 1";
  const Board b = FenToBoard(fen);
  const vector<Move> moves = GeneratePseudoLegalMoves(b);
  ASSERT(!HasMove(moves, whiteKingCastle));
  ASSERT(HasMove(moves, whiteQueenCastle));
}

TEST(MovegenBlackCastleDifferingFlags) {
  const string fen = "r3k2r/8/8/8/8/8/8/R3K2R b k - 0 1";
  const Board b = FenToBoard(fen);
  const vector<Move> moves = GeneratePseudoLegalMoves(b);
  ASSERT(HasMove(moves, blackKingCastle));
  ASSERT(!HasMove(moves, blackQueenCastle));
}

TEST(MovegenWhiteCastleBlockedByCheck) {
  const string fen = "r3k2r/8/8/8/8/8/3p4/R3K2R w KQkq - 0 1";
  const Board b = FenToBoard(fen);
  const vector<Move> moves = GeneratePseudoLegalMoves(b);
  ASSERT(!HasMove(moves, whiteKingCastle));
  ASSERT(!HasMove(moves, whiteQueenCastle));
}

TEST(MovegenWhiteKingCastleBlockedByAttack) {
  const string fen = "r3k2r/8/8/8/8/3b4/8/R3K2R w KQkq - 0 1";
  const Board b = FenToBoard(fen);
  const vector<Move> moves = GeneratePseudoLegalMoves(b);
  ASSERT(!HasMove(moves, whiteKingCastle));
  ASSERT(HasMove(moves, whiteQueenCastle));
}

TEST(MovegenWhiteQueenCastleBlockedByAttack) {
  const string fen = "r3k2r/8/8/8/8/2n5/8/R3K2R w KQkq - 0 1";
  const Board b = FenToBoard(fen);
  const vector<Move> moves = GeneratePseudoLegalMoves(b);
  ASSERT(HasMove(moves, whiteKingCastle));
  ASSERT(!HasMove(moves, whiteQueenCastle));
}

TEST(MovegenBlackCastleBlockedByCheck) {
  const string fen = "r3k2r/8/8/8/Q7/8/8/R3K2R b KQkq - 0 1";
  const Board b = FenToBoard(fen);
  const vector<Move> moves = GeneratePseudoLegalMoves(b);
  ASSERT(!HasMove(moves, blackKingCastle));
  ASSERT(!HasMove(moves, blackQueenCastle));
}

TEST(MovegenBlackKingCastleBlockedByAttack) {
  const string fen = "r3k2r/8/6N1/8/8/8/8/R3K2R b KQkq - 0 1";
  const Board b = FenToBoard(fen);
  const vector<Move> moves = GeneratePseudoLegalMoves(b);
  ASSERT(!HasMove(moves, blackKingCastle));
  ASSERT(HasMove(moves, blackQueenCastle));
}

TEST(MovegenBlackQueenCastleBlockedByAttack) {
  const string fen = "r3k2r/3R4/8/8/8/8/8/4K3 b KQkq - 0 1";
  const Board b = FenToBoard(fen);
  const vector<Move> moves = GeneratePseudoLegalMoves(b);
  ASSERT(HasMove(moves, blackKingCastle));
  ASSERT(!HasMove(moves, blackQueenCastle));
}

TEST(MovegenWhiteEnPassantCapture) {
  const string fen = "k7/8/8/3pP3/8/8/8/K7 w KQkq d6 0 1";
  const Board b = FenToBoard(fen);
  const vector<Move> moves = GeneratePseudoLegalMoves(b);
  ASSERT(HasMove(moves, Move("e5d6", true, Pawn)));
}

TEST(MovegenWhiteEnPassantUnavailable) {
  const string fen = "k7/8/8/3pP3/8/8/8/K7 w KQkq - 0 1";
  const Board b = FenToBoard(fen);
  const vector<Move> moves = GeneratePseudoLegalMoves(b);
  ASSERT(!HasMove(moves, Move("e5d6")));
}

TEST(MovegenBlackEnPassantCapture) {
  const string fen = "k7/8/8/8/3pP3/8/8/K7 b KQkq e3 0 1";
  const Board b = FenToBoard(fen);
  const vector<Move> moves = GeneratePseudoLegalMoves(b);
  ASSERT(HasMove(moves, Move("d4e3", true, Pawn)));
}

TEST(MovegenBlackEnPassantUnavailable) {
  const string fen = "k7/8/8/8/3pP3/8/8/K7 b KQkq - 0 1";
  const Board b = FenToBoard(fen);
  const vector<Move> moves = GeneratePseudoLegalMoves(b);
  ASSERT(!HasMove(moves, Move("d4e3")));
}
