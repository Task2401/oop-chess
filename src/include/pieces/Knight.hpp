#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include <vector>

#include "Piece.hpp"

// @class Knight
// @brief Represents a Knight piece in chess.

class Knight : public Piece {
    public:

        // @brief Constructs a Knight of the specified color.
        // @param c The color of the knight.

        Knight(Color c);

        // @brief Destructor for Knight

        ~Knight() override;

        // @brief Generates L-shaped pseudo-legal moves for the knight.
        // @param board Current state of the chess board.
        // @param currentPos Current position of the Knight
        // @return Vector of pseudo-legal moves.

        std::vector<Move> getPseudoLegalMoves(const ChessBoard& board, Position currentPos) const override;
};

#endif // KNIGHT_HPP
