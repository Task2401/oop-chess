#ifndef KING_HPP
#define KING_HPP

#include <vector>

#include "Piece.hpp"

/**
* @class King
* @brief Represents a King Piece in chess.
*/

class King : public Piece {
    public:
    
        /**
        * @brief Constructs a King of the specified color.
        * @param c The color of the king.
        */

        King(Color c);
    
        /**
        * @brief Destructor for King.
        */

        ~King() override;

        /**
        * @brief Generates pseudo-legal moves for the king (including castling checks)
        * @param board Current state of the chess board.
        * @param currentPos Current position of the king.
        * @return Vector of pseudo-legal moves.
        */

        std::vector<Move> getPseudoLegalMoves(const ChessBoard& board, Position currentPos) const override;
};

#endif // KING_HPP
