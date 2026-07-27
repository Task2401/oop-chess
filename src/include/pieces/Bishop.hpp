#ifndef BISHOP_HPP
#define BISHOP_HPP

#include "Piece.hpp"
#include <vector>

class Bishop : public Piece {
    public:
        Bishop(Color c);
        ~Bishop() override;

        std::vector<Move> getPseudoLegalMoves(const ChessBoard& board, Position currentPos) const override;
};
 
#endif 
