#include "board.h"
#include "catch.hpp"
#include "fen.h"
#include "move.h"
#include "movegen.h"
#include "piece-moves.h"
#include "std.h"

// Helper function for finding a move in a list of moves.
bool HasMove(const vector<Move>& v, const Move& m) {
  for (const Move& x : v) {
    if (x == m) {
      return true;
    }
  }
  return false;
}

TEST_CASE("Movegen: opening position", "[Movegen]") {
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
  REQUIRE(actual == expected);
}

TEST_CASE("Movegen: white pawn promotion without capture", "[Movegen]") {
  const string fen = "8/4P3/8/8/8/8/8/8 w - - 0 1";
  const Board b = FenToBoard(fen);
  const vector<Move> moves = GeneratePseudoLegalMoves(b);
  const vector<string> actual = MovesToStrings(moves);
  // 20 possible moves from the opening position.
  const vector<string> expected = { "e7e8b", "e7e8n", "e7e8q", "e7e8r" };
  REQUIRE(actual == expected);
}

TEST_CASE("Movegen: white pawn promotion with capture", "[Movegen]") {
  const string fen = "3qkb2/4P3/8/8/8/8/8/8 w - - 0 1";
  const Board b = FenToBoard(fen);
  const vector<Move> moves = GeneratePseudoLegalMoves(b);
  const vector<string> actual = MovesToStrings(moves);
  // 20 possible moves from the opening position.
  const vector<string> expected = { "e7d8b", "e7d8n", "e7d8q", "e7d8r",
                                    "e7f8b", "e7f8n", "e7f8q", "e7f8r" };
  REQUIRE(actual == expected);
}

TEST_CASE("Movegen: black pawn promotion without capture", "[Movegen]") {
  const string fen = "8/8/8/8/8/8/2p5/8 b - - 0 1";
  const Board b = FenToBoard(fen);
  const vector<Move> moves = GeneratePseudoLegalMoves(b);
  const vector<string> actual = MovesToStrings(moves);
  // 20 possible moves from the opening position.
  const vector<string> expected = { "c2c1b", "c2c1n", "c2c1q", "c2c1r" };
  REQUIRE(actual == expected);
}

TEST_CASE("Movegen: black pawn promotion with capture", "[Movegen]") {
  const string fen = "8/8/8/8/8/8/6p1/5Q2 b - - 0 1";
  const Board b = FenToBoard(fen);
  const vector<Move> moves = GeneratePseudoLegalMoves(b);
  const vector<string> actual = MovesToStrings(moves);
  // 20 possible moves from the opening position.
  const vector<string> expected = { "g2f1b", "g2f1n", "g2f1q", "g2f1r",
                                    "g2g1b", "g2g1n", "g2g1q", "g2g1r" };
  REQUIRE(actual == expected);
}

TEST_CASE("Movegen: sliding piece capture", "[Movegen]") {
  const string fen = "8/8/8/1R3n2/8/8/8/8 w - - 0 1";
  const Board b = FenToBoard(fen);
  const vector<Move> moves = GeneratePseudoLegalMoves(b);
  const vector<string> actual = MovesToStrings(moves);
  // 20 possible moves from the opening position.
  const vector<string> expected = { "b5a5", "b5b1", "b5b2", "b5b3",
                                    "b5b4", "b5b6", "b5b7", "b5b8",
                                    "b5c5", "b5d5", "b5e5", "b5f5" };
  REQUIRE(actual == expected);
  // Check capture b5f5 properly marked as a capture move.
  REQUIRE(HasMove(moves, Move("b5f5", true, Knight)));
  // Does not contain non-capture b5f5.
  REQUIRE_FALSE(HasMove(moves, Move("b5f5")));
  // Check capture b5f5 captures the right piece type, knight.
  REQUIRE_FALSE(HasMove(moves, Move("b5f5", true, Bishop)));
  // Check one of the non-capture moves to make sure it isn't a capture.
  REQUIRE(HasMove(moves, Move("b5c5")));
  REQUIRE_FALSE(HasMove(moves, Move("b5c5", true, Knight)));
}

TEST_CASE("Movegen: white castle with all options open", "[Movegen]") {
  const string fen = "r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1";
  const Board b = FenToBoard(fen);
  const vector<Move> moves = GeneratePseudoLegalMoves(b);
  REQUIRE(moves.size() == 26);
  REQUIRE(HasMove(moves, whiteKingCastle));
  REQUIRE(HasMove(moves, whiteQueenCastle));
  REQUIRE_FALSE(HasMove(moves, blackKingCastle));
  REQUIRE_FALSE(HasMove(moves, blackQueenCastle));
}

TEST_CASE("Movegen: black castle with all options open", "[Movegen]") {
  const string fen = "r3k2r/8/8/8/8/8/8/R3K2R b KQkq - 0 1";
  const Board b = FenToBoard(fen);
  const vector<Move> moves = GeneratePseudoLegalMoves(b);
  REQUIRE(moves.size() == 26);
  REQUIRE(HasMove(moves, blackKingCastle));
  REQUIRE(HasMove(moves, blackQueenCastle));
  REQUIRE_FALSE(HasMove(moves, whiteKingCastle));
  REQUIRE_FALSE(HasMove(moves, whiteQueenCastle));
}

TEST_CASE("Movegen: white castle blocked by flags", "[Movegen]") {
  const string fen = "r3k2r/8/8/8/8/8/8/R3K2R w - - 0 1";
  const Board b = FenToBoard(fen);
  const vector<Move> moves = GeneratePseudoLegalMoves(b);
  REQUIRE_FALSE(HasMove(moves, whiteKingCastle));
  REQUIRE_FALSE(HasMove(moves, whiteQueenCastle));
}

TEST_CASE("Movegen: black castle blocked by flags", "[Movegen]") {
  const string fen = "r3k2r/8/8/8/8/8/8/R3K2R b - - 0 1";
  const Board b = FenToBoard(fen);
  const vector<Move> moves = GeneratePseudoLegalMoves(b);
  REQUIRE_FALSE(HasMove(moves, blackKingCastle));
  REQUIRE_FALSE(HasMove(moves, blackQueenCastle));
}

TEST_CASE("Movegen: white castle differing flags", "[Movegen]") {
  const string fen = "r3k2r/8/8/8/8/8/8/R3K2R w Q - 0 1";
  const Board b = FenToBoard(fen);
  const vector<Move> moves = GeneratePseudoLegalMoves(b);
  REQUIRE_FALSE(HasMove(moves, whiteKingCastle));
  REQUIRE(HasMove(moves, whiteQueenCastle));
}

TEST_CASE("Movegen: black castle differing flags", "[Movegen]") {
  const string fen = "r3k2r/8/8/8/8/8/8/R3K2R b k - 0 1";
  const Board b = FenToBoard(fen);
  const vector<Move> moves = GeneratePseudoLegalMoves(b);
  REQUIRE(HasMove(moves, blackKingCastle));
  REQUIRE_FALSE(HasMove(moves, blackQueenCastle));
}

TEST_CASE("Movegen: white castle blocked by check", "[Movegen]") {
  const string fen = "r3k2r/8/8/8/8/8/3p4/R3K2R w KQkq - 0 1";
  const Board b = FenToBoard(fen);
  const vector<Move> moves = GeneratePseudoLegalMoves(b);
  REQUIRE_FALSE(HasMove(moves, whiteKingCastle));
  REQUIRE_FALSE(HasMove(moves, whiteQueenCastle));
}

TEST_CASE("Movegen: white king castle blocked by attack", "[Movegen]") {
  const string fen = "r3k2r/8/8/8/8/3b4/8/R3K2R w KQkq - 0 1";
  const Board b = FenToBoard(fen);
  const vector<Move> moves = GeneratePseudoLegalMoves(b);
  REQUIRE_FALSE(HasMove(moves, whiteKingCastle));
  REQUIRE(HasMove(moves, whiteQueenCastle));
}

TEST_CASE("Movegen: white queen castle blocked by attack", "[Movegen]") {
  const string fen = "r3k2r/8/8/8/8/2n5/8/R3K2R w KQkq - 0 1";
  const Board b = FenToBoard(fen);
  const vector<Move> moves = GeneratePseudoLegalMoves(b);
  REQUIRE(HasMove(moves, whiteKingCastle));
  REQUIRE_FALSE(HasMove(moves, whiteQueenCastle));
}

TEST_CASE("Movegen: black castle blocked by check", "[Movegen]") {
  const string fen = "r3k2r/8/8/8/Q7/8/8/R3K2R b KQkq - 0 1";
  const Board b = FenToBoard(fen);
  const vector<Move> moves = GeneratePseudoLegalMoves(b);
  REQUIRE_FALSE(HasMove(moves, blackKingCastle));
  REQUIRE_FALSE(HasMove(moves, blackQueenCastle));
}

TEST_CASE("Movegen: black king castle blocked by attack", "[Movegen]") {
  const string fen = "r3k2r/8/6N1/8/8/8/8/R3K2R b KQkq - 0 1";
  const Board b = FenToBoard(fen);
  const vector<Move> moves = GeneratePseudoLegalMoves(b);
  REQUIRE_FALSE(HasMove(moves, blackKingCastle));
  REQUIRE(HasMove(moves, blackQueenCastle));
}

TEST_CASE("Movegen: black queen castle blocked by attack", "[Movegen]") {
  const string fen = "r3k2r/3R4/8/8/8/8/8/4K3 b KQkq - 0 1";
  const Board b = FenToBoard(fen);
  const vector<Move> moves = GeneratePseudoLegalMoves(b);
  REQUIRE(HasMove(moves, blackKingCastle));
  REQUIRE_FALSE(HasMove(moves, blackQueenCastle));
}

TEST_CASE("Movegen: white en passant capture", "[Movegen]") {
  const string fen = "k7/8/8/3pP3/8/8/8/K7 w KQkq d6 0 1";
  const Board b = FenToBoard(fen);
  const vector<Move> moves = GeneratePseudoLegalMoves(b);
  REQUIRE(HasMove(moves, Move("e5d6", true, Pawn)));
}

TEST_CASE("Movegen: white en passant unavailable", "[Movegen]") {
  const string fen = "k7/8/8/3pP3/8/8/8/K7 w KQkq - 0 1";
  const Board b = FenToBoard(fen);
  const vector<Move> moves = GeneratePseudoLegalMoves(b);
  REQUIRE_FALSE(HasMove(moves, Move("e5d6")));
}

TEST_CASE("Movegen: black en passant capture", "[Movegen]") {
  const string fen = "k7/8/8/8/3pP3/8/8/K7 b KQkq e3 0 1";
  const Board b = FenToBoard(fen);
  const vector<Move> moves = GeneratePseudoLegalMoves(b);
  REQUIRE(HasMove(moves, Move("d4e3", true, Pawn)));
}

TEST_CASE("Movegen: black en passant unavailable", "[Movegen]") {
  const string fen = "k7/8/8/8/3pP3/8/8/K7 b KQkq - 0 1";
  const Board b = FenToBoard(fen);
  const vector<Move> moves = GeneratePseudoLegalMoves(b);
  REQUIRE_FALSE(HasMove(moves, Move("d4e3")));
}
