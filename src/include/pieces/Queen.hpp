#ifndef QUEEN_HPP
#define QUEEN_HPP

#include <vector>

#include "Piece.hpp" 

/**
* @class Queen
* @brief Represents a Queen piece in chess.
*/

class Queen : public Piece {
    public:

        /**
        * @brief Constructs a Queen of the specified color.
        * @param c The color of the queen.
        */

        Queen(Color c);

        /**
        * @brief Destructor for Queen.
        */

        ~Queen() override;

        /**
        * @brief Generates combined orthogonal and diagonal pseudo-legal move for the queen.
        * @param board Current state if the chess board.
        * @param currentPos Current position of the queen.
        * @return Vector of pseudo-legal moves.
        */

        std::vector<Move> getPseudoLegalMoves(const ChessBoard& board, Position currenPos) const override;
};

#endif // QUEEN_HPP 
