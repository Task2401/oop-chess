#ifndef COMMON_HPP
#define COMMON_HPP

enum Color{
    COLOR_NONE,
    WHITE,
    BLACK
};

enum PieceType {
    PIECE_NONE,
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
};

enum Difficulty {
    EASY,
    MEDIUM,
    HARD
};

struct Position {
    char file;
    char rank;
};


struct Move {
    Position start;
    Position end;
    PieceType movedPiece;
    PieceType capturedPiece;
    PieceType promotedTo;
    bool isCastling;
    bool isEnPassant;
    bool isPromotion;
};

Position createPosition(char file, char rank);
Move createEmptyMove();

bool operator==(const Position& a, const Position& b);
bool operator!=(const Position& a, const Position& b);
bool operator==(const Move& a, const Move& b);

#endif

