#ifndef CHESS_ENGINE_HPP
#define CHESS_ENGINE_HPP

#include <vector>
#include "ChessBoard.hpp"
#include "Common.hpp"

class ChessEngine {
    private:
        ChessBoard board;

    public:
        ChessEngine();
        ~ChessEngine();

        std::vector<Move> filterLegalMoves(const std::vector<Move> pseudoMoves) const;
        std::vector<Move> getAllLegalMoves() const;

        bool isSquareAttacked(Position pos, Color attackerColor) const;
        bool executeMove(Move move);
        bool isCheck() const;
        bool isCheckmate() const;
        bool isStalemate() const;
        
        ChessBoard getBoard() const;
};  

#endif
