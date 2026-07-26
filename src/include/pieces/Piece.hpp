#ifndef PIECE_HPP
#define PIECE_HPP

#include <vector>
#include "../core/Common.hpp"

class ChessBoard;

class Piece {
    protected:
        Color color;
        char symbol;

    public:
        Piece(Color c, char s); 
        virtual ~Piece() = default;

        Color getColor() const;
        char getSymbol() const;
        virtual  std::vector<Move> getPseudoLegalMoves(const ChessBoard& board, Position currentPos) const = 0;

};

#endif
 
