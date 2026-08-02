#ifndef PAWN_HPP
#define PAWN_HPP

#include <vector>

#include "Piece.hpp"

// @class Pawn
// @brief Represents a Pawn piece in chess.

class Pawn : public Piece {
    public:

        // @brief Constucts a Pawn of the specified color.
        // @param c The color of the pawn.

        Pawn(Color c);

        // @brief Destructor for Pawn

        ~Pawn() override;

        // @brief Generates pseudo-legal moves for the pawn (pushes, captures, en passant, promotion).
        // @param board Current state   of the chess board.
        // @param currentPos Current position of the pawn.
        // @return Vector of pseudo-legal moves.

        std::vector<Move> getPseudoLegalMoves(const ChessBoard& board, Position currentPos) const override;
};

#endif // PAWN_HPP 
