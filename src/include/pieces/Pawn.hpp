#ifndef PAWN_HPP
#define PAWN_HPP

#include "Piece.hpp"

class Pawn : public Piece {
    public:
        Pawn(Color c);
        ~Pawn() override;

        std::vector<Move> getPseudoLegalMoves(const ChessBoard& board, Position currentPos) const override;
};

#endif
