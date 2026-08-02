#ifndef BISHOP_HPP
#define BISHOP_HPP

#include <vector>

#include "Piece.hpp"

// @class Bishop
// @brief Represents a Bishop piece in chess.

class Bishop : public Piece {
    public:

        // @brief Constructs a Bishop of the specified color.
        // @param c The color of the bishop.

        Bishop(Color c);

        // @brief Destructor for Bishop/

        ~Bishop() override;

        // @brief Gnerates diagonal pseudo-legal moves for the bishop.
        // @param board Current state of the chess board.
        // @param currentPos Current position of the bishop.
        // @return Vector of pseudo-legal moves.

        std::vector<Move> getPseudoLegalMoves(const ChessBoard& board, Position currentPos) const override;
};
 
#endif  // BISHOP_HPP
