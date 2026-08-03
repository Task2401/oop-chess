#ifndef CHESS_ENGINE_HPP
#define CHESS_ENGINE_HPP

#include <vector>

#include "ChessBoard.hpp"
#include "Common.hpp"

/**
 *  @class ChessEngine
 * @brief Handles chess rules, legal move generation, and game state evaluations.
 */

class ChessEngine {
    private:
        ChessBoard board;   // Internal representation of the active game board.

    public:
        
        /**
         * @brief Constructor / Destructor
         */
         
        ChessEngine();
        ~ChessEngine();

        /**
         * @brief Filters pseudo-legal moves down to strictly legal moves (removes moves that leave King in check)
         * @param pseudoMoves Vector of candidate pseudo-legal moves
         * @return Vector of valid legal moves.
         */
         
        std::vector<Move> filterLegalMoves(const std::vector<Move>&   pseudoMoves) const;
        
        /** 
         * @brief Generates all fully legal moves available for the current player.
         * @return Vector containing all legal moves.
        */

        std::vector<Move> getAllLegalMoves() const;

        /**
         * @brief Checks if a specific square is under attack by a given player side.
         *  @param pos Square positspecificon to check.
         * @param attackerColor Color of the attacking side.
         * @return True if the square is threatened, false otherwise.
         */
                 
        bool isSquareAttacked(Position pos, Color attackerColor) const;
        
        /**
         * @brief Validates and executes a move on the board if legal.
         * @param move The move to be made.
         * @return True if successful, false if illegal.
         */
       
        bool executeMove(Move move);

        /**
        * @brief Checks if the current player is in check.
        * @return True if in check, false otherwise
        */

        bool isCheck() const;
 
        /**
        * @brief Checks if the current player is in check.
        * @return True if in check, false otherwise.
        */

        bool isCheckmate() const;

        /**
        * @brief Checks if the current position is a stalemate (draw).
        * @return True if game is stalemate, false otherwise.
        */

        bool isStalemate() const;
         
        /**
        * @brief Retrieves a copy of the current board instance.
        * @return ChessBoard object representing current state.
        */

        ChessBoard getBoard() const;
};  

#endif // CHESS_ENGINE_HPP
