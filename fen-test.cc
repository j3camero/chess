#include "board.h"
#include "catch.hpp"
#include "fen.h"
#include "piece.h"
#include "std.h"

TEST_CASE("Read default start position", "[FEN]") {
  const string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  Board b = FenToBoard(fen);
  REQUIRE(b.color[0][0] == Black);
  REQUIRE(b.piece[0][0] == Rook);
  REQUIRE(b.color[0][4] == Black);
  REQUIRE(b.piece[0][4] == King);
  REQUIRE(b.color[0][7] == Black);
  REQUIRE(b.piece[0][7] == Rook);
  REQUIRE(b.color[1][3] == Black);
  REQUIRE(b.piece[1][3] == Pawn);
  REQUIRE(b.color[2][5] == Empty);
  REQUIRE(b.color[5][1] == Empty);
  REQUIRE(b.color[6][2] == White);
  REQUIRE(b.piece[6][2] == Pawn);
  REQUIRE(b.color[7][0] == White);
  REQUIRE(b.piece[7][0] == Rook);
  REQUIRE(b.color[7][4] == White);
  REQUIRE(b.piece[7][4] == King);
  REQUIRE(b.color[7][7] == White);
  REQUIRE(b.piece[7][7] == Rook);
  REQUIRE(b.turn == White);
  REQUIRE(b.opp == Black);
  REQUIRE(b.whiteKingCastle == true);
  REQUIRE(b.whiteQueenCastle == true);
  REQUIRE(b.blackKingCastle == true);
  REQUIRE(b.blackQueenCastle == true);
  REQUIRE(b.enPassantFile == -1);
  REQUIRE(b.halfmoveClock == 0);
  REQUIRE(b.moveCount == 1);
}

TEST_CASE("Read position with assorted scattered pieces", "[FEN]") {
  const string fen = "1n3n2/1p3p2/R2Q2bk/8/8/r2q2B1/1P2KP2/P1N5 w KQkq - 0 1";
  Board b = FenToBoard(fen);
  Color expectedColor[8][8] = {
    {Empty, Black, Empty, Empty, Empty, Black, Empty, Empty},
    {Empty, Black, Empty, Empty, Empty, Black, Empty, Empty},
    {White, Empty, Empty, White, Empty, Empty, Black, Black},
    {Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty},
    {Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty},
    {Black, Empty, Empty, Black, Empty, Empty, White, Empty},
    {Empty, White, Empty, Empty, White, White, Empty, Empty},
    {White, Empty, White, Empty, Empty, Empty, Empty, Empty}
  };
  for (int rank = 0; rank < 8; rank++) {
    for (int file = 0; file < 8; file++) {
      REQUIRE(b.color[rank][file] == expectedColor[rank][file]);
    }
  }
  REQUIRE(b.piece[0][1] == Knight);
}

TEST_CASE("Read position with only one piece", "[FEN]") {
  const string fen = "8/8/8/2k5/8/8/8/8 w KQkq - 0 1";
  Board b = FenToBoard(fen);
  REQUIRE(b.color[3][2] == Black);
  REQUIRE(b.piece[3][2] == King);
  REQUIRE(b.color[3][3] == Empty);
  REQUIRE(b.color[3][1] == Empty);
  REQUIRE(b.color[2][2] == Empty);
  REQUIRE(b.color[4][2] == Empty);
}

TEST_CASE("White to move", "[FEN]") {
  const string fen = "8/8/8/8/8/8/8/8 w KQkq - 0 1";
  Board b = FenToBoard(fen);
  REQUIRE(b.turn == White);
  REQUIRE(b.opp == Black);
}

TEST_CASE("Black to move", "[FEN]") {
  const string fen = "8/8/8/8/8/8/8/8 b KQkq - 0 1";
  Board b = FenToBoard(fen);
  REQUIRE(b.turn == Black);
  REQUIRE(b.opp == White);
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
