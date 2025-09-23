#include "board.h"
#include "fen.h"
#include "point.h"
#include "piece.h"
#include "std.h"
#include "string-util.h"

// Parses one rank of piece placement data from the first token of a FEN string.
// fen - one rank of a chessboard. Ex: "rnbqkbnr", "PPPPPPPP", "4P3", "8".
// rank - which rank to place the encoded piece on the chessboard.
// board (output) - one rank of the given Board's squares will be overwritten.
void ParseOneRank(const string& fen, int rank, Board& board) {
  int file = 0;
  for (const char& c : fen) {
    if (StringUtil::IsDigit(c)) {
  	  const int digit = StringUtil::DigitToInt(c);
	    for (int j = 0; j < digit; j++) {
	      board.color[rank][file] = Empty;
	      file++;
  	  }
    } else {
      Color color;
  	  Piece piece;
      CharToPiece(c, color, piece);
  	  board.color[rank][file] = color;
  	  board.piece[rank][file] = piece;
      if (piece == King) {
        if (color == White) {
          board.whiteKingLocation = Point(rank, file);
        } else {
          board.blackKingLocation = Point(rank, file);
        }
      }
	    file++;
    }
    // Bail early if a rank of FEN tries to specify more than 8 squares.
    if (file >= 8) {
  	  break;
    }
  }
  // Each rank of FEN should specify exactly 8 squares.
  if (file != 8) {
    throw "Wrong number of squares. Should be 8.";
  }
}

// Parses the first token of a FEN string, piece placement.
// piecePLacement: the first token of a FEN string.
// board (output): the given Board's squares will be overwritten.
void ParsePiecePlacement(const string& piecePlacement, Board& board) {
  board.whiteKingLocation = Point(-1, -1);
  board.blackKingLocation = Point(-1, -1);
  const vector<string> tokens = StringUtil::Split(piecePlacement, '/');
  if (tokens.size() != 8) {
    throw "Wrong number of ranks. Should be 8.";
  }
  int rank = 0;
  for (const string& token : tokens) {
    ParseOneRank(token, rank, board);
    rank++;
  }
}

// Parses the second token of a FEN string, side to move.
// sideToMove: the second token of a FEN string. Must be "w" or "b".
// board (output): the given Board's side-to-move will be overwritten.
void ParseSideToMove(const string& sideToMove, Board& board) {
  if (sideToMove.size() != 1) {
    throw "Invalid side-to-move. Must be a single character.";
  }
  char c = sideToMove[0];
  switch (c) {
  case 'b':
    board.turn = Black;
    board.opp = White;
    break;
  case 'w':
    board.turn = White;
    board.opp = Black;
    break;
  default:
    throw "Invalid side-to-move. Must be w or b.";
  }
}

// Parses the third token of a FEN string, castle status.
// castleStatus: the third token of a FEN string.
// board (output): the given Board's castle flags will be overwritten.
void ParseCastleStatus(const string& castleStatus, Board& board) {
  if (castleStatus.size() > 4) {
    throw "Invalid castle status.";
  }
  board.irreversible.ClearWhiteKingCastle();
  board.irreversible.ClearWhiteQueenCastle();
  board.irreversible.ClearBlackKingCastle();
  board.irreversible.ClearBlackQueenCastle();
  for (const char c : castleStatus) {
    switch (c) {
    case 'K':
      board.irreversible.SetWhiteKingCastle();
      break;
    case 'Q':
      board.irreversible.SetWhiteQueenCastle();
      break;
    case 'k':
      board.irreversible.SetBlackKingCastle();
      break;
    case 'q':
      board.irreversible.SetBlackQueenCastle();
      break;
    case '-':
      break;
    default:
      throw "Invalid castle status.";
    }
  }
}

// Parses the fourth token of a FEN string, en-passant target square.
// enPassantTargetString: the fourth token of a FEN string.
// board (output): the given Board's en-passant flags will be overwritten.
void ParseEnPassant(const string& enPassantTargetString, Board& board) {
  if (enPassantTargetString == "-") {
    // -1 means there is no en-passant move available.
    board.irreversible.enPassantFile = -1;
  } else if (enPassantTargetString.size() == 2) {
    Point p(enPassantTargetString);
    board.irreversible.enPassantFile = p.file;
  } else {
    throw "Invalid en-passant target square.";
  }
}

// Parses the fifth token of a FEN string, the halfmove clock.
// The halfmove clock is used for the 50-move rule.
// halfmove: the fifth token of a FEN string.
// board (output): the given Board's halfmove clock will be overwritten.
void ParseHalfmoveClock(const string& halfmove, Board& board) {
  try {
    board.irreversible.halfmoveClock = (unsigned char)stoi(halfmove);
  } catch (...) {
    throw "Halfmove clock is not an integer: " + halfmove;
  }
}

// Parses the sixth token of a FEN string, the move count.
// moveCount: the sixth token of a FEN string.
// board (output): the given Board's move count will be overwritten.
void ParseMoveNumber(const string& moveCount, Board& board) {
  try {
    board.moveCount = stoi(moveCount);
  } catch (...) {
    throw "Move count is not an integer: " + moveCount;
  }
}

Board FenToBoard(const string& fen) {
  vector<string> tokens = StringUtil::Split(fen);
  if (tokens.size() != 6) {
    throw "Invalid FEN string. A FEN string should have exactly 6 parts.";
  }
  try {
    Board board;
    ParsePiecePlacement(tokens[0], board);
    ParseSideToMove(tokens[1], board);
    ParseCastleStatus(tokens[2], board);
    ParseEnPassant(tokens[3], board);
    ParseHalfmoveClock(tokens[4], board);
    ParseMoveNumber(tokens[5], board);
    return board;
  } catch (const string& e) {
    throw "Invalid FEN string. " + e;
  }
}

string BoardToFen(const Board& b) {
  string fen = "";
  for (int rank = 0; rank < 8; rank++) {
    int emptyCount = 0;
    for (int file = 0; file < 8; file++) {
      Color c = b.color[rank][file];
      if (c == Empty) {
        emptyCount++;
      } else {
        if (emptyCount > 0) {
          fen += to_string(emptyCount);
          emptyCount = 0;
        }
        Piece p = b.piece[rank][file];
        fen += PieceToChar(c, p);
      }
    }
    if (emptyCount > 0) {
      fen += to_string(emptyCount);
    }
    if (rank < 7) {
      fen += "/";
    }
  }
  fen += " ";
  if (b.turn == White) {
    fen += "w";
  } else {
    fen += "b";
  }
  fen += " ";
  bool anyCastle = false;
  if (b.irreversible.WhiteKingCastleAllowed()) {
    fen += "K";
    anyCastle = true;
  }
  if (b.irreversible.WhiteQueenCastleAllowed()) {
    fen += "Q";
    anyCastle = true;
  }
  if (b.irreversible.BlackKingCastleAllowed()) {
    fen += "k";
    anyCastle = true;
  }
  if (b.irreversible.BlackQueenCastleAllowed()) {
    fen += "q";
    anyCastle = true;
  }
  if (!anyCastle) {
    fen += "-";
  }
  fen += " ";
  int epf = b.irreversible.enPassantFile;
  if (epf < 0) {
    fen += "-";
  } else {
    int epRank = (b.opp == White) ? 5 : 2;
    Point p(epRank, epf);
    fen += p.ToString();
  }
  fen += " ";
  fen += to_string((int)b.irreversible.halfmoveClock);
  fen += " ";
  fen += to_string(b.moveCount);
  return fen;
}
