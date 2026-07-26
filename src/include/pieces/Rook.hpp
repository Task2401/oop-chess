#ifndef ROOK_HPP
#define ROOK_HPP

#include <vector>
#include "Piece.hpp"

class Rook : public Piece {
    public:
        Rook(Color c);
        ~Rook() override;

        std::vector<Move> getPseudoLegalMoves(const ChessBoard& board, Position currentPos) const override;
};

#endif
