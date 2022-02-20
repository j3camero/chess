#include "board.h"
#include "fen.h"
#include "piece.h"
#include "std.h"
#include "string-util.h"

Board FenToBoard(const string& fen) {
  Board board;
  vector<string> tokens = StringUtil::Split(fen);
  if (tokens.size() != 6) {
    throw "Invalid FEN string.";
  }
  const string piecePlacement = tokens[0];
  const string activeColorString = tokens[1];
  const string castleString = tokens[2];
  const string enPassantTargetString = tokens[3];
  const string halfmoveClockString = tokens[4];
  const string fullMoveNumberString = tokens[5];
  const vector<string> ranks = StringUtil::Split(piecePlacement, '/');
  if (ranks.size() != 8) {
    throw "Invalid FEN string.";
  }
  int rank = 0;
  for (const string& rankString : ranks) {
    int file = 0;
    for (const char& c : rankString) {
      if (StringUtil::IsDigit(c)) {
	const int digit = StringUtil::DigitToInt(c);
	for (int j = 0; j < digit; j++) {
	  board.squares[rank][file] = Empty;
	  file++;
	}
      } else {
	Piece piece = CharToPiece(c);
	board.squares[rank][file] = piece;
	file++;
      }
      // Bail early if a rank of FEN tries to specify more than 8 squares.
      if (file >= 8) {
	break;
      }
    }
    // Each rank of FEN should specify exactly 8 squares.
    if (file != 8) {
      throw "Invalid FEN string.";
    }
    rank++;
  }
  return board;
}

string BoardToFen(const Board& b) {
  return "";
}
