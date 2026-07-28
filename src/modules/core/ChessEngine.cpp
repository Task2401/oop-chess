#include <iostream>
#include <string>
#include <vector>

#include "../../include/core/ChessEngine.hpp"

using namespace std;

ChessEngine::ChessEngine() : board() {
    cout << "ChessEngine created succesfully!" << endl;
}

ChessEngine::~ChessEngine() {
    cout << "ChessEngine destroyed succesfully!"<< endl;
}

vector<Move> ChessEngine::filterLegalMoves(const vector<Move> pseudoMoves) const {
    vector<Move> legalMoves;

    // ...

    return legalMoves;
}

vector<Move> ChessEngine::getAllLegalMoves() const {
    vector<Move> allMoves;

    // ...

    return allMoves;
}

bool ChessEngine::isSquareAttacked(Position pos, Color attackerColor) const {
    auto isWithinBoard = [](char file, char rank) {
        return (file >= 'a' && file <= 'h' && rank >= '1' && rank <= '8');
    };

    int knightFileMoves[] = {1, 2, 2 ,1, -1, -2, -2, -1};
    int knightRankMoves[] = {2, 1, -1, -2, -2, -1, 1, 2};
    string enemyKnight = (attackerColor == WHITE) ? "N" : "n";

    for (int i = 0; i < 8; i++) {
        char targetFile = pos.file + knightFileMoves[i];
        char targetRank = pos.rank + knightRankMoves[i];
        if (isWithinBoard(targetFile, targetRank))
            if (board.getPieceAt(createPosition(targetFile, targetRank)) == enemyKnight) return true;
    }

    int pawnFileMoves[] = {-1, 1};
    int pawnRankDirections = (attackerColor == WHITE) ? -1 : 1;
    string enemyPawn = (attackerColor == WHITE) ? "P" : "p";
    
    for (int i = 0; i < 2; i++) {
        char targetFile = pos.file + pawnFileMoves[i];
        char targetRank = pos.rank + pawnRankDirections;
        if (isWithinBoard(targetFile, targetRank))
            if (board.getPieceAt((createPosition(targetFile, targetRank))) == enemyPawn) return true;
    }

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
                break;
            }
            targetFile += straightFileMoves[i];
            targetRank += straightRankMoves[i];
        }
    }

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
                break;
            }
            targetFile += diagFileMoves[i];
            targetRank += diagRankMoves[i];
        }
    }

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

bool ChessEngine::executeMove(Move move)  {

    // ...

    return false;
}

bool ChessEngine::isCheck() const {
    
    // ...

    return false;
}

bool ChessEngine::isCheckmate() const {
    
    // ...

    return false;
}

bool ChessEngine::isStalemate() const {

    // ...

    return false;
}


ChessBoard ChessEngine::getBoard() const {
    return board;
}


