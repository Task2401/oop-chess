#ifndef ROOK_HPP
#define ROOK_HPP

#include <vector>

#include "Piece.hpp" 

// @class Rook
// @brief Represents a Rook piece in chess.

class Rook : public Piece {
    public:

        // @brief Constructs a Rook of the specified color.
        // @param c The color of the rook.

        Rook(Color c);

        // @brief Destructor for Rook

        ~Rook() override;

        // @brief Generates  orthogonal (rank/file) pseudo-legal moves for the rook.
        // @param board Current state of the chess board.
        // @param currentPos Current position of the rook.
        // @return Vector of pseudo-legal moves.

        std::vector<Move> getPseudoLegalMoves(const ChessBoard& board, Position currentPos) const override;
};

#endif // ROOK_HPP
