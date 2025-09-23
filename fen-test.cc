#include "board.h"
#include "fen.h"
#include "point.h"
#include "piece.h"
#include "std.h"
#include "test.h"

TEST(FenOpeningPosition) {
  const string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  Board b = FenToBoard(fen);
  ASSERT(b.color[0][0] == Black);
  ASSERT(b.piece[0][0] == Rook);
  ASSERT(b.color[0][4] == Black);
  ASSERT(b.piece[0][4] == King);
  ASSERT(b.color[0][7] == Black);
  ASSERT(b.piece[0][7] == Rook);
  ASSERT(b.color[1][3] == Black);
  ASSERT(b.piece[1][3] == Pawn);
  ASSERT(b.color[2][5] == Empty);
  ASSERT(b.color[5][1] == Empty);
  ASSERT(b.color[6][2] == White);
  ASSERT(b.piece[6][2] == Pawn);
  ASSERT(b.color[7][0] == White);
  ASSERT(b.piece[7][0] == Rook);
  ASSERT(b.color[7][4] == White);
  ASSERT(b.piece[7][4] == King);
  ASSERT(b.color[7][7] == White);
  ASSERT(b.piece[7][7] == Rook);
  ASSERT(b.turn == White);
  ASSERT(b.opp == Black);
  ASSERT(b.irreversible.WhiteKingCastleAllowed());
  ASSERT(b.irreversible.WhiteQueenCastleAllowed());
  ASSERT(b.irreversible.BlackKingCastleAllowed());
  ASSERT(b.irreversible.BlackQueenCastleAllowed());
  ASSERT(b.irreversible.enPassantFile == -1);
  ASSERT(b.irreversible.halfmoveClock == 0);
  ASSERT(b.moveCount == 1);
  ASSERT(b.whiteKingLocation == Point(7, 4));
  ASSERT(b.blackKingLocation == Point(0, 4));
  string outputShouldMatchTheInput = BoardToFen(b);
  ASSERT(outputShouldMatchTheInput == fen);
}

TEST(FenPositionWithAssortedScatteredPieces) {
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
      ASSERT(b.color[rank][file] == expectedColor[rank][file]);
    }
  }
  ASSERT(b.piece[0][1] == Knight);
  ASSERT(b.whiteKingLocation == Point(6, 4));
  ASSERT(b.blackKingLocation == Point(2, 7));
  string outputShouldMatchTheInput = BoardToFen(b);
  ASSERT(outputShouldMatchTheInput == fen);
}

TEST(FenPositionWithOnlyOnePiece) {
  const string fen = "8/8/8/2k5/8/8/8/8 w KQkq - 0 1";
  Board b = FenToBoard(fen);
  ASSERT(b.color[3][2] == Black);
  ASSERT(b.piece[3][2] == King);
  ASSERT(b.color[3][3] == Empty);
  ASSERT(b.color[3][1] == Empty);
  ASSERT(b.color[2][2] == Empty);
  ASSERT(b.color[4][2] == Empty);
  ASSERT(b.whiteKingLocation == Point(-1, -1));
  ASSERT(b.blackKingLocation == Point(3, 2));
  string outputShouldMatchTheInput = BoardToFen(b);
  ASSERT(outputShouldMatchTheInput == fen);
}

TEST(FenWhiteToMove) {
  const string fen = "8/8/8/8/8/8/8/8 w KQkq - 0 1";
  Board b = FenToBoard(fen);
  ASSERT(b.turn == White);
  ASSERT(b.opp == Black);
  string outputShouldMatchTheInput = BoardToFen(b);
  ASSERT(outputShouldMatchTheInput == fen);
}

TEST(FenBlackToMove) {
  const string fen = "8/8/8/8/8/8/8/8 b KQkq - 0 1";
  Board b = FenToBoard(fen);
  ASSERT(b.turn == Black);
  ASSERT(b.opp == White);
  string outputShouldMatchTheInput = BoardToFen(b);
  ASSERT(outputShouldMatchTheInput == fen);
}

TEST(FenUnparseableSideToMove) {
  const string fen = "8/8/8/8/8/8/8/8 r KQkq - 0 1";
  ASSERT_EXCEPTION(FenToBoard(fen));
}

TEST(FenCastle) {
  const string fen = "8/8/8/8/8/8/8/8 b KQkq - 0 1";
  Board b = FenToBoard(fen);
  ASSERT(b.irreversible.WhiteKingCastleAllowed());
  ASSERT(b.irreversible.WhiteQueenCastleAllowed());
  ASSERT(b.irreversible.BlackKingCastleAllowed());
  ASSERT(b.irreversible.BlackQueenCastleAllowed());
  string outputShouldMatchTheInput = BoardToFen(b);
  ASSERT(outputShouldMatchTheInput == fen);
}

TEST(FenNoCastleAllowed) {
  const string fen = "8/8/8/8/8/8/8/8 b - - 0 1";
  Board b = FenToBoard(fen);
  ASSERT(b.irreversible.WhiteKingCastleAllowed() == false);
  ASSERT(b.irreversible.WhiteQueenCastleAllowed() == false);
  ASSERT(b.irreversible.BlackKingCastleAllowed() == false);
  ASSERT(b.irreversible.BlackQueenCastleAllowed() == false);
  string outputShouldMatchTheInput = BoardToFen(b);
  ASSERT(outputShouldMatchTheInput == fen);
}

TEST(FenCastleUnparseable) {
  const string fen = "8/8/8/8/8/8/8/8 b Krkq - 0 1";
  ASSERT_EXCEPTION(FenToBoard(fen));
}

TEST(FenCastleMixedValues) {
  const string fen = "8/8/8/8/8/8/8/8 b Qk - 0 1";
  Board b = FenToBoard(fen);
  ASSERT(b.irreversible.WhiteKingCastleAllowed() == false);
  ASSERT(b.irreversible.WhiteQueenCastleAllowed() == true);
  ASSERT(b.irreversible.BlackKingCastleAllowed() == true);
  ASSERT(b.irreversible.BlackQueenCastleAllowed() == false);
  string outputShouldMatchTheInput = BoardToFen(b);
  ASSERT(outputShouldMatchTheInput == fen);
}

TEST(FenCastleBlackQueen) {
  const string fen = "8/8/8/8/8/8/8/8 b q - 0 1";
  Board b = FenToBoard(fen);
  ASSERT(b.irreversible.WhiteKingCastleAllowed() == false);
  ASSERT(b.irreversible.WhiteQueenCastleAllowed() == false);
  ASSERT(b.irreversible.BlackKingCastleAllowed() == false);
  ASSERT(b.irreversible.BlackQueenCastleAllowed() == true);
  string outputShouldMatchTheInput = BoardToFen(b);
  ASSERT(outputShouldMatchTheInput == fen);
}

TEST(FenEnPassantWhiteSide) {
  const string fen = "8/8/8/8/8/8/8/8 w - e6 7 1";
  Board b = FenToBoard(fen);
  ASSERT(b.irreversible.enPassantFile == 4);
  string outputShouldMatchTheInput = BoardToFen(b);
  ASSERT(outputShouldMatchTheInput == fen);
}

TEST(FenEnPassantBlackSide) {
  const string fen = "8/8/8/8/8/8/8/8 b - h3 7 1";
  Board b = FenToBoard(fen);
  ASSERT(b.irreversible.enPassantFile == 7);
  string outputShouldMatchTheInput = BoardToFen(b);
  ASSERT(outputShouldMatchTheInput == fen);
}

TEST(FenEnPassantUnavailable) {
  const string fen = "8/8/8/8/8/8/8/8 b - - 7 1";
  Board b = FenToBoard(fen);
  ASSERT(b.irreversible.enPassantFile == -1);
  string outputShouldMatchTheInput = BoardToFen(b);
  ASSERT(outputShouldMatchTheInput == fen);
}

TEST(FenEnPassantUnparseable) {
  const string fen = "8/8/8/8/8/8/8/8 w - i5 7 1";
  ASSERT_EXCEPTION(FenToBoard(fen));
}

TEST(FenHalfMoveClock) {
  const string fen = "8/8/8/8/8/8/8/8 w KQkq - 7 1";
  Board b = FenToBoard(fen);
  ASSERT(b.irreversible.halfmoveClock == 7);
  string outputShouldMatchTheInput = BoardToFen(b);
  ASSERT(outputShouldMatchTheInput == fen);
}

TEST(FenMoveCount) {
  const string fen = "8/8/8/8/8/8/8/8 b KQkq - 7 42";
  Board b = FenToBoard(fen);
  ASSERT(b.moveCount == 42);
  string outputShouldMatchTheInput = BoardToFen(b);
  ASSERT(outputShouldMatchTheInput == fen);
}
