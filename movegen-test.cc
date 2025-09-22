#include "board.h"
#include "fen.h"
#include "move.h"
#include "movegen.h"
#include "piece-moves.h"
#include "std.h"
#include "test.h"

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

TEST(MovingIntoCheckIsIllegal) {
  // TODO: make unit test for full-on legal move generation (not pseudo legal).
  ASSERT(true);
}
