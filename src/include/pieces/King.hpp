#ifndef KING_HPP
#define KING_HPP

#include <vector>
#include "Piece.hpp"

class King : public Piece {
    public:
        King(Color c);
        ~King() override;

        std::vector<Move> getPseudoLegalMoves(const ChessBoard& board, Position currentPos) const override;
};

#endif
