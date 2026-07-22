#include "../../include/core/Common.hpp"

Position createPosition(char file, char rank) {
    Position pos;

    pos.file = file;
    pos.rank = rank;
    
    return pos;
}

Move createEmptyMove() {
    Move move;

    move.start = createPosition('-', '-');
    move.end = createPosition('-', '-');
    move.movedPiece = PIECE_NONE;
    move.capturedPiece = PIECE_NONE;
    move.promotedTo = PIECE_NONE;
    move.isCastling = false;
    move.isEnPassant = false;
    move.isPromotion = false;
    
    return move;
}

bool operator==(const Position& a, const Position& b) {
    return a.file == b.file && a.rank == b.rank;
}

bool operator!=(const Position& a, const Position& b) {
    return !(a == b);
}

bool operator==(const Move& a, const Move& b) {
    return a.start == b.start && a.end == b.end &&
     a.movedPiece == b.movedPiece && a.capturedPiece == b.capturedPiece &&
     a.isCastling == b.isCastling && a.isEnPassant == b.isEnPassant &&
     a.isPromotion == b.isPromotion && a.promotedTo == b.promotedTo;
}