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
        void printChessBoard() const;
        void clearSquare(const Position& gridPos);
        void makeMove(const Move& move);
        
        void setPieceAt(const Position& piecePos, const std::string& pieceStr);
        

        int getRow(const Position& gridPos) const;
        int getCol(const Position& gridPos) const;
        std::string getPieceAt(const Position& piecePos) const;
        Color getActiveColor() const;
};


#endif