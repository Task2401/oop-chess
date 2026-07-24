#ifndef CHESSBOARD_HPP
#define CHESSBOARD_HPP

#include <string>

#include "../core/Common.hpp"

class ChessBoard {
    private:
        std::string chessGrid[8][8];
        Color activateColor;
        Position enPassantTarget;
        bool canCastleKingside[3];
        bool canCastleQueenside[3];
        int halfMoveClock;
        int fullMoveNumber;

    public:
        ChessBoard();
        ~ChessBoard();

        void setupChessBoard();
        void printChessBoard();

        std::string getPieceAt(const Position& piecePos) const;
        void setPieceAt(const Position& piecePos, std::string& pieceStr);
        void clearSquere(const Position& gridPos);

        void makeMove(const Move& move);
        
        Color getActiveColor() const;

};


#endif