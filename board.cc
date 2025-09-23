#include "board.h"

bool Board::operator==(const Board& other) const {
  bool debug = false;
  if (turn != other.turn) {
    if (debug) cout << "turn" << endl;
    return false;
  }
  if (opp != other.opp) {
    if (debug) cout << "opp" << endl;
    return false;
  }
  if (moveCount != other.moveCount) {
    if (debug) cout << "moveCount" << endl;
    return false;
  }
  if (irreversible.castleBits != other.irreversible.castleBits) {
    if (debug) cout << "castleBits" << endl;
    return false;
  }
  if (irreversible.enPassantFile != other.irreversible.enPassantFile) {
    if (debug) cout << "enPassantFile" << endl;
    return false;
  }
  if (irreversible.halfmoveClock != other.irreversible.halfmoveClock) {
    if (debug) cout << "halfmoveClock" << endl;
    return false;
  }
  if (whiteKingLocation != other.whiteKingLocation) {
    if (debug) cout << "whiteKingLocation" << endl;
    return false;
  }
  if (blackKingLocation != other.blackKingLocation) {
    if (debug) cout << "blackKingLocation" << endl;
    return false;
  }
  for (int rank = 0; rank < 8; rank++) {
    for (int file = 0; file < 8; file++) {
      if (color[rank][file] != other.color[rank][file]) {
        if (debug) cout << "color " << rank << " " << file << endl;
        return false;
      }
      if (color[rank][file] != Empty) {
        if (piece[rank][file] != other.piece[rank][file]) {
          if (debug) cout << "piece " << rank << " " << file << endl;
          return false;
        }
      }
    }
  }
  return true;
}

bool Board::operator!=(const Board& other) const {
  return !(*this == other);
}
