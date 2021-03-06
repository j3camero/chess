#include "board.h"
#include "catch.hpp"
#include "fen.h"
#include "piece.h"
#include "std.h"

TEST_CASE("Read default start position", "[FEN]") {
  const string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  Board b = FenToBoard(fen);
  REQUIRE(b.squares[0][0] == BlackRook);
  REQUIRE(b.squares[0][4] == BlackKing);
  REQUIRE(b.squares[0][7] == BlackRook);
  REQUIRE(b.squares[1][3] == BlackPawn);
  REQUIRE(b.squares[2][5] == Empty);
  REQUIRE(b.squares[5][1] == Empty);
  REQUIRE(b.squares[6][2] == WhitePawn);
  REQUIRE(b.squares[7][0] == WhiteRook);
  REQUIRE(b.squares[7][4] == WhiteKing);
  REQUIRE(b.squares[7][7] == WhiteRook);
  REQUIRE(b.move == White);
  REQUIRE(b.whiteKingCastle == true);
  REQUIRE(b.whiteQueenCastle == true);
  REQUIRE(b.blackKingCastle == true);
  REQUIRE(b.blackQueenCastle == true);
  REQUIRE(b.enPassantFile == -1);
  REQUIRE(b.halfmoveClock == 0);
  REQUIRE(b.moveCount == 1);
}

TEST_CASE("Read position with only one piece", "[FEN]") {
  const string fen = "8/8/8/2k5/8/8/8/8 w KQkq - 0 1";
  Board b = FenToBoard(fen);
  REQUIRE(b.squares[3][2] == BlackKing);
  REQUIRE(b.squares[3][3] == Empty);
  REQUIRE(b.squares[3][1] == Empty);
  REQUIRE(b.squares[2][2] == Empty);
  REQUIRE(b.squares[4][2] == Empty);
}

TEST_CASE("White to move", "[FEN]") {
  const string fen = "8/8/8/8/8/8/8/8 w KQkq - 0 1";
  Board b = FenToBoard(fen);
  REQUIRE(b.move == White);
}

TEST_CASE("Black to move", "[FEN]") {
  const string fen = "8/8/8/8/8/8/8/8 b KQkq - 0 1";
  Board b = FenToBoard(fen);
  REQUIRE(b.move == Black);
}

TEST_CASE("Unparseable side to move", "[FEN]") {
  const string fen = "8/8/8/8/8/8/8/8 r KQkq - 0 1";
  REQUIRE_THROWS(FenToBoard(fen));
}

TEST_CASE("Castle", "[FEN]") {
  const string fen = "8/8/8/8/8/8/8/8 b KQkq - 0 1";
  Board b = FenToBoard(fen);
  REQUIRE(b.whiteKingCastle == true);
  REQUIRE(b.whiteQueenCastle == true);
  REQUIRE(b.blackKingCastle == true);
  REQUIRE(b.blackQueenCastle == true);
}

TEST_CASE("Castle: no castle allowed", "[FEN]") {
  const string fen = "8/8/8/8/8/8/8/8 b - - 0 1";
  Board b = FenToBoard(fen);
  REQUIRE(b.whiteKingCastle == false);
  REQUIRE(b.whiteQueenCastle == false);
  REQUIRE(b.blackKingCastle == false);
  REQUIRE(b.blackQueenCastle == false);
}

TEST_CASE("Castle: unparseable", "[FEN]") {
  const string fen = "8/8/8/8/8/8/8/8 b Krkq - 0 1";
  REQUIRE_THROWS(FenToBoard(fen));
}

TEST_CASE("Castle: mixed values", "[FEN]") {
  const string fen = "8/8/8/8/8/8/8/8 b kQ - 0 1";
  Board b = FenToBoard(fen);
  REQUIRE(b.whiteKingCastle == false);
  REQUIRE(b.whiteQueenCastle == true);
  REQUIRE(b.blackKingCastle == true);
  REQUIRE(b.blackQueenCastle == false);
}

TEST_CASE("Castle: Black Queen", "[FEN]") {
  const string fen = "8/8/8/8/8/8/8/8 b q - 0 1";
  Board b = FenToBoard(fen);
  REQUIRE(b.whiteKingCastle == false);
  REQUIRE(b.whiteQueenCastle == false);
  REQUIRE(b.blackKingCastle == false);
  REQUIRE(b.blackQueenCastle == true);
}

TEST_CASE("En passant white side", "[FEN]") {
  const string fen = "8/8/8/8/8/8/8/8 w - e5 7 1";
  Board b = FenToBoard(fen);
  REQUIRE(b.enPassantFile == 4);
}

TEST_CASE("En passant black side", "[FEN]") {
  const string fen = "8/8/8/8/8/8/8/8 b - h4 7 1";
  Board b = FenToBoard(fen);
  REQUIRE(b.enPassantFile == 7);
}

TEST_CASE("En passant unavailable", "[FEN]") {
  const string fen = "8/8/8/8/8/8/8/8 b - - 7 1";
  Board b = FenToBoard(fen);
  REQUIRE(b.enPassantFile == -1);
}

TEST_CASE("En passant unparseable", "[FEN]") {
  const string fen = "8/8/8/8/8/8/8/8 w - i5 7 1";
  REQUIRE_THROWS(FenToBoard(fen));
}

TEST_CASE("Halfmove clock", "[FEN]") {
  const string fen = "8/8/8/8/8/8/8/8 w KQkq - 7 1";
  Board b = FenToBoard(fen);
  REQUIRE(b.halfmoveClock == 7);
}

TEST_CASE("Move count", "[FEN]") {
  const string fen = "8/8/8/8/8/8/8/8 b KQkq - 7 42";
  Board b = FenToBoard(fen);
  REQUIRE(b.moveCount == 42);
}
