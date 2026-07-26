#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include "Piece.hpp"
#include <vector>

class Knight : public Piece {
    public:
        Knight(Color c);
        ~Knight() override;

        std::vector<Move> getPseudoLegalMoves(const ChessBoard& board, Position currentPos) const override;
};

#endif
