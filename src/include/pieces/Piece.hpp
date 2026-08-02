#ifndef PIECE_HPP
#define PIECE_HPP

#include <vector>

#include "../core/Common.hpp"

// Forward declaration of ChessBoard to avoid circular depedencies

class ChessBoard;

// @class Piece
// @brief Abstract base class representing a generic class piece.

class Piece {
    protected:
        Color color;    // Color of the piece (WHITE, BLACK).
        char symbol;    // Character representation of the piece (e.g., 'P', 'N', 'K').
    public:

        // @brief Constructs a Piece with given color and symbol.
        // @param c The color of the piece.
        // @param s The symbol representing the piece

        Piece(Color c, char s); 

        // @brief Virtual destructor for clean inheritance.

        virtual ~Piece() = default;

        // @brief Gets the color of the piece
        // @return Color enum value.

        Color getColor() const;

        // @brief Gets the character symbol of the piece.
        // @return char representing the piece

        char getSymbol() const;

        // @brief Pure virtual method to generate psudo-legal moves for this piece.
        // @param bo Reference to the current ChessBoard state.
        // @param currentPos The square position where the piece is currently locate.
        // @return Vector of candinate psudo-legal moves.

        virtual  std::vector<Move> getPseudoLegalMoves(const ChessBoard& board, Position currentPos) const = 0;

};

#endif
 
