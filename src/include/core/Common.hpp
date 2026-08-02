#ifndef COMMON_HPP
#define COMMON_HPP

// @brief Represents the color of  a piece or player side.

enum Color{
    COLOR_NONE,
    WHITE,
    BLACK
};

// @brief Represents the type of a chess piece.

enum PieceType {
    PIECE_NONE,
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
};

// @brief Difficulty levels for AI/Engine settings.

enum Difficulty {
    EASY,
    MEDIUM,
    HARD
};

// @brief Represents a square on the chessboard using file (column) and rank (row).

struct Position {
    char file; // e.g., 'a' through 'h'
    char rank; // e,g., '1' through '8'
};

// @brief Represents a move on the chessboard, including special move flags

struct Move {
    Position start;             // Starting square
    Position end;               // Target square
    PieceType movedPiece;       // Type of the piece being moved
    PieceType capturedPiece;    // Type of captured piece (PIECE_NONE if none)
    PieceType promotedTo;       // Type of piece promoted (PIECE_NONE if not promotion)
    bool isCastling;            // Flag for castling move
    bool isEnPassant;           // Flag for en passant capture
    bool isPromotion;           // Flag for pawn promotion
};

// Utility functions declarations.

Position createPosition(char file, char rank);
Move createEmptyMove();

// Equality operator overloads for comparison

bool operator==(const Position& a, const Position& b);
bool operator!=(const Position& a, const Position& b);
bool operator==(const Move& a, const Move& b);

#endif // COMMON_HPP

