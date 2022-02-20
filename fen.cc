#include "board.h"
#include "fen.h"
#include "point.h"
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
  const string activeColorString = tokens[1];
  if (activeColorString.size() != 1) {
    throw "Invalid FEN string.";
  }
  char activeColorChar = activeColorString[0];
  switch (activeColorChar) {
  case 'b':
    board.move = Black;
    break;
  case 'w':
    board.move = White;
    break;
  default:
    throw "Invalid FEN string.";
  }
  const string castleString = tokens[2];
  if (castleString.size() > 4) {
    throw "Invalid FEN string.";
  }
  board.whiteKingCastle = false;
  board.whiteQueenCastle = false;
  board.blackKingCastle = false;
  board.blackQueenCastle = false;
  for (const char c : castleString) {
    switch (c) {
    case 'K':
      board.whiteKingCastle = true;
      break;
    case 'Q':
      board.whiteQueenCastle = true;
      break;
    case 'k':
      board.blackKingCastle = true;
      break;
    case 'q':
      board.blackQueenCastle = true;
      break;
    case '-':
      break;
    default:
      throw "Invalid FEN string.";
    }
  }
  const string enPassantTargetString = tokens[3];
  if (enPassantTargetString == "-") {
    // -1 means there is no en-passant move available.
    board.enPassantFile = -1;
  } else if (enPassantTargetString.size() == 2) {
    Point p(enPassantTargetString);
    board.enPassantFile = p.file;
  } else {
    throw "Invalid FEN string.";
  }
  const string halfmoveClockString = tokens[4];
  const string fullMoveNumberString = tokens[5];
  return board;
}

string BoardToFen(const Board& b) {
  return "";
}
