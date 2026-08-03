#ifndef CHESSBOARD_HPP
#define CHESSBOARD_HPP

#include <string>

#include "Common.hpp"

/**
* @class ChessBoard
* @brief Manages the state and layout of the chessboard.
*/

class ChessBoard {
    private:
        std::string chessGrid[8][8];    // 8x8 representation of the board state
        Color activateColor;            // Color of the player whose turn it is to move                                      
        Position enPassantTarget;       // Target square for en passant captures
        bool canCastleKingside[3];      // Kingside castling rights [0: unused/indexing. 1: WHITE, 2: BLACK]
        bool canCastleQueenside[3];     // Queenside castling rights [0: unused/indexing. 1: WHITE, 2: BLACK]
        int halfMoveClock;              // Half-move clock for fifty-move rule
        int fullMoveNumber;             // Total full moves (incremented after Black moves)

    public:

        /**
        * @brief Constructor / Destructor.
        */

        ChessBoard();
        ~ChessBoard();

        /**
        * @brief Initialize the board to the standard starting position.
        */

        void setupChessBoard();

        /**
        * @brief Displays the current state of the board to stdout/console.
        */

        void printChessBoard() const;
       
        /**
        * @brief Clear the specified square on the board
        * @param gridPos Position to clear
        */

        void clearSquare(const Position& gridPos);
        
        /**
        * @brief Updates the board state by applying a given move.
        * @param move The move to perform
        */

        void makeMove(const Move& move);
        
        /**
        * @brief Sets a piece string representation at a specific position.
        * @param piecePos Target position.
        * @param pieceStr String representation of the piece.
        */

        void setPieceAt(const Position& piecePos, const std::string& pieceStr);
        
        // Getters / Helper methods

        int getRow(const Position& gridPos) const;
        int getCol(const Position& gridPos) const;
        std::string getPieceAt(const Position& piecePos) const;
        Color getActiveColor() const;
        Position getEnPassantTarget() const;
};


#endif // CHESSBOARD_HPP
