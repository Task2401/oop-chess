#include <iostream>
#include <string>
#include <vector>
#include <cctype>


#include "../../include/core/ChessEngine.hpp"
#include "../../include/pieces/Pawn.hpp"
#include "../../include/pieces/Knight.hpp"
#include "../../include/pieces/Bishop.hpp"
#include "../../include/pieces/Rook.hpp"
#include "../../include/pieces/Queen.hpp"
#include "../../include/pieces/King.hpp"

using namespace std;

// Constructor

ChessEngine::ChessEngine() : board() {
    cout << "ChessEngine created succesfully!" << endl;
}

// Destructor

ChessEngine::~ChessEngine() {
    cout << "ChessEngine destroyed succesfully!"<< endl;
}

// Filters out pseudo-legal moves that leave or place the active player's King in check.

vector<Move> ChessEngine::filterLegalMoves(const vector<Move>& pseudoMoves) const {
    vector<Move> legalMoves;

    Color myColor = board.getActiveColor();
    Color opponentColor = (myColor == WHITE) ? BLACK : WHITE;
    string myKing = (myColor == WHITE) ? "K" : "k";

    for (const Move& move : pseudoMoves) {

        // Simulate move on a temporary board instance.

        ChessEngine tempEngine = *this;
        tempEngine.board.makeMove(move);

        Position kingPos;
        bool kingFound = false;

        // Locate King position on the simulated board.

        for (char file = 'a'; file <= 'h'; file++) {
            for (char rank = '1'; rank <= '8'; rank++) {
                Position pos = createPosition(file, rank);
                if (tempEngine.board.getPieceAt(pos) == myKing) {
                    kingPos = pos;
                    kingFound = true;
                    break;
                }
            }
            if (kingFound) break;
        }

        // Keep move if King is not under attack after executing it.

        if (kingFound && !tempEngine.isSquareAttacked(kingPos, opponentColor)) 
            legalMoves.push_back(move); 
    }
    return legalMoves;
}

// Collects all fully legal moves available for the active player

vector<Move> ChessEngine::getAllLegalMoves() const {
    vector<Move> pseudoMoves;
    Color myColor = board.getActiveColor();
   
    // Helper lambda to check if a piece belongs to current player.

    auto isMyPiece = [](const string& piece, Color color) {
        if (piece == " " || piece.empty()) return false;
        if (color == WHITE) return isupper(piece[0]) != 0;
        return islower(piece[0]) != 0;
    };

    // Iterate over all board positions
        
    for (char file = 'a'; file <= 'h'; file++) {
        for (char rank = '1'; rank <= '8'; rank++) {
            Position pos = createPosition(file, rank);
            string pieceStr = board.getPieceAt(pos);

            if (isMyPiece(pieceStr, myColor)) {
                char pieceType = tolower(pieceStr[0]);
                vector<Move> pieceMoves;

                // Instantiate corresponding piece class to obtain pseudo-legal moves.

                switch (pieceType) {
                    case 'p': {
                        Pawn pawn(myColor);
                        pieceMoves = pawn.getPseudoLegalMoves(board, pos);
                        break;
                    }

                    case 'n': {
                        Knight knight(myColor);
                        pieceMoves = knight.getPseudoLegalMoves(board, pos);
                        break;
                    }

                    case 'b' : {
                        Bishop bishop(myColor);
                        pieceMoves = bishop.getPseudoLegalMoves(board, pos);
                        break;
                    }

                    case 'r' : {
                        Rook rook(myColor);
                        pieceMoves = rook.getPseudoLegalMoves(board, pos);
                        break;
                    }

                    case 'q' : {
                        Queen queen(myColor);
                        pieceMoves = queen.getPseudoLegalMoves(board, pos);
                        break;
                    }

                    case 'k' : {
                        King king(myColor);
                        pieceMoves = king.getPseudoLegalMoves(board, pos);
                        break;
                    } 
                }
                pseudoMoves.insert(pseudoMoves.end(), pieceMoves.begin(), pieceMoves.end());
            }
        }
    }

    // Returns only strictly legal moves.

    return filterLegalMoves(pseudoMoves);
}

// Determines if a specific target square is under attack by any piece of attackerColor.

bool ChessEngine::isSquareAttacked(Position pos, Color attackerColor) const {
    auto isWithinBoard = [](char file, char rank) {
        return (file >= 'a' && file <= 'h' && rank >= '1' && rank <= '8');
    };

    // Check for Knight attacks

    int knightFileMoves[] = {1, 2, 2 ,1, -1, -2, -2, -1};
    int knightRankMoves[] = {2, 1, -1, -2, -2, -1, 1, 2};
    string enemyKnight = (attackerColor == WHITE) ? "N" : "n";

    for (int i = 0; i < 8; i++) {
        char targetFile = pos.file + knightFileMoves[i];
        char targetRank = pos.rank + knightRankMoves[i];
        if (isWithinBoard(targetFile, targetRank))
            if (board.getPieceAt(createPosition(targetFile, targetRank)) == enemyKnight) return true;
    }

    // Check for pawn attacks

    int pawnFileMoves[] = {-1, 1};
    int pawnRankDirections = (attackerColor == WHITE) ? -1 : 1;
    string enemyPawn = (attackerColor == WHITE) ? "P" : "p";
    
    for (int i = 0; i < 2; i++) {
        char targetFile = pos.file + pawnFileMoves[i];
        char targetRank = pos.rank + pawnRankDirections;
        if (isWithinBoard(targetFile, targetRank))
            if (board.getPieceAt((createPosition(targetFile, targetRank))) == enemyPawn) return true;
    }

    // Check for Straight attacks (Rook or Queen)

    int straightFileMoves[] = {0, 0, 1, -1};
    int straightRankMoves[] = {1, -1, 0, 0};
    string enemyRook = (attackerColor == WHITE) ? "R" : "r";
    string enemyQueen = (attackerColor == WHITE) ? "Q" : "q";

    for (int i = 0; i < 4; i++) {
        char targetFile = pos.file + straightFileMoves[i];
        char targetRank = pos.rank + straightRankMoves[i];
        while (isWithinBoard(targetFile, targetRank)) {
            string piece = board.getPieceAt(createPosition(targetFile, targetRank));
            if (piece != " ") {
                if (piece == enemyRook || piece == enemyQueen) {
                    return true;
                }
                break; // Obstacle encountered
            }
            targetFile += straightFileMoves[i];
            targetRank += straightRankMoves[i];
        }
    }

    // Check for Diagonal attacks (Bishop and Queen)

    int diagFileMoves[] = {1, 1, -1, -1};
    int diagRankMoves[] = {1, -1, 1, -1};
    string enemyBishop = (attackerColor == WHITE) ? "B" : "b";

    for (int i = 0; i < 4; i++) {
        char targetFile = pos.file + diagFileMoves[i];
        char targetRank = pos.rank + diagRankMoves[i];
        while (isWithinBoard(targetFile, targetRank)) {
            string piece = board.getPieceAt(createPosition(targetFile, targetRank));
            if (piece != " ") {
                if (piece == enemyBishop || piece == enemyQueen) {
                    return true;
                }
                break; // Obstacle encountered
            }
            targetFile += diagFileMoves[i];
            targetRank += diagRankMoves[i];
        }
    }

    // Check for adjacent King attacks

    int kingFileMoves[] = {0, 0, 1, -1, 1, 1, -1, -1};
    int kingRankMoves[] = {1, -1, 0, 0, 1, -1, 1, -1};
    string enemyKing = (attackerColor == WHITE) ? "K" : "k";

    for (int i = 0; i < 8; i++) {
        char targetFile = pos.file + kingFileMoves[i];
        char targetRank = pos.rank + kingRankMoves[i];
        if (isWithinBoard(targetFile, targetRank))
            if(board.getPieceAt(createPosition(targetFile, targetRank)) == enemyKing) return true;
    }
    return false;
}

// Verifies if requested move is legal and executes it on the board.

bool ChessEngine::executeMove(Move move)  {
    vector<Move> legalMoves = getAllLegalMoves();
    
    bool moveFound = false;
    Move verifiedMove;

    for (const Move& legalMove : legalMoves) {
        if (legalMove.start == move.start &&
            legalMove.end == move.end &&
            legalMove.promotedTo == move.promotedTo) {

            verifiedMove = legalMove;
            moveFound = true;
            break;
        }
    }

    if (moveFound) {
        board.makeMove(verifiedMove);
        return true;
    }

    return false; // Requested move is illegal
}

// Checks if the active player's King is currently in Check

bool ChessEngine::isCheck() const {
    Color currentTurn = board.getActiveColor();

    string myKing = (currentTurn == WHITE) ? "K" : "k";
    Color enemyColor = (currentTurn == WHITE) ? BLACK : WHITE;

    Position kingPos;
    bool kingFound = false;

    // Locates active player's King position

    for (char file = 'a'; file <= 'h'; file++) {
        for (char rank = '1'; rank <= '8'; rank++) {
            Position pos = createPosition(file, rank);
            if (board.getPieceAt(pos) == myKing) {
                kingPos = pos;
                kingFound = true;
                break;
            }
        }
        if (kingFound) break;
    }

    if (!kingFound) return false;

    return isSquareAttacked(kingPos, enemyColor);
}

// Returns true if current position is Checkmate (in check with no legal moves)

bool ChessEngine::isCheckmate() const {
    return  isCheck() && getAllLegalMoves().empty();
}

// Returns true if current position is Stalemate (no in check with no legal moves)

bool ChessEngine::isStalemate() const {
    return !isCheck() && getAllLegalMoves().empty();
}

// Returns current internal ChessBoard instance.

ChessBoard ChessEngine::getBoard() const {
    return board;
}


