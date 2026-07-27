#ifndef QUEEN_HPP
#define QUEEN_HPP

#include <vector>
#include "Piece.hpp"

class Queen : public Piece {
    public:
        Queen(Color c);
        ~Queen() override;

        std::vector<Move> getPseudoLegalMoves(const ChessBoard& board, Position currenPos) const override;
};

#endif
