#ifndef EVALUATOR_HPP
#define EVALUATOR_HPP

#include "../core/ChessBoard.hpp"

#define VAL_PAWN   100
#define VAL_KNIGHT 300
#define VAL_BISHOP 320
#define VAL_ROOK   500
#define VAL_QUEEN  900


class Evaluator {
    public:
        static const int pawnPST[8][8];
        static const int knightPST[8][8];
        static const int bishopPST[8][8];
        static const int rookPST[8][8];
        static const int queenPST[8][8];
        static const int kingMiddlePST[8][8];

        Evaluator();
        ~Evaluator();

        int getMaterialValue(char piece) const;
        int getPositionalValue(char piece, char file, char rank) const;
    
        int evaluate(const ChessBoard& board) const;


};


#endif
