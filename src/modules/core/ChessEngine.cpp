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

ChessEngine::ChessEngine() : board() {
    cout << "ChessEngine created succesfully!" << endl;
}

ChessEngine::~ChessEngine() {
    cout << "ChessEngine destroyed succesfully!"<< endl;
}

vector<Move> ChessEngine::filterLegalMoves(const vector<Move>& pseudoMoves) const {
    vector<Move> legalMoves;

    Color myColor = board.getActiveColor();
    Color opponentColor = (myColor == WHITE) ? BLACK : WHITE;
    string myKing = (myColor == WHITE) ? "K" : "k";

    for (const Move& move : pseudoMoves) {
        ChessEngine tempEngine = *this;
        tempEngine.board.makeMove(move);

        Position kingPos;
        bool kingFound = false;

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
        if (kingFound && !tempEngine.isSquareAttacked(kingPos, opponentColor)) 
            legalMoves.push_back(move); 
    }
    return legalMoves;
}

vector<Move> ChessEngine::getAllLegalMoves() const {
    vector<Move> pseudoMoves;
    Color myColor = board.getActiveColor();
    
    auto isMyPiece = [](const string& piece, Color color) {
        if (piece == " " || piece.empty()) return false;
        if (color == WHITE) return isupper(piece[0]) != 0;
        return islower(piece[0]) != 0;
    };
        
    for (char file = 'a'; file <= 'h'; file++) {
        for (char rank = '1'; rank <= '8'; rank++) {
            Position pos = createPosition(file, rank);
            string pieceStr = board.getPieceAt(pos);

            if (isMyPiece(pieceStr, myColor)) {
                char pieceType = tolower(pieceStr[0]);
                vector<Move> pieceMoves;

                switch (pieceType) {
                    case 'p': {
                        Pawn p(myColor);
                        pieceMoves = p.getPseudoLegalMoves(board, pos);
                        break;
                    }

                    case 'n': {
                        Knight n(myColor);
                        pieceMoves = n.getPseudoLegalMoves(board, pos);
                        break;
                    }

                    case 'b' : {
                        Bishop b(myColor);
                        pieceMoves = b.getPseudoLegalMoves(board, pos);
                        break;
                    }

                    case 'r' : {
                        Rook r(myColor);
                        pieceMoves = r.getPseudoLegalMoves(board, pos);
                        break;
                    }

                    case 'q' : {
                        Queen q(myColor);
                        pieceMoves = q.getPseudoLegalMoves(board, pos);
                        break;
                    }

                    case 'k' : {
                        King k(myColor);
                        pieceMoves = k.getPseudoLegalMoves(board, pos);
                        break;
                    } 
                }
                pseudoMoves.insert(pseudoMoves.end(), pieceMoves.begin(), pieceMoves.end());
            }
        }
    }

    return filterLegalMoves(pseudoMoves);
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

    return false;
}

bool ChessEngine::isCheck() const {
    Color currentTurn = board.getActiveColor();

    string myKing = (currentTurn == WHITE) ? "K" : "k";
    Color enemyColor = (currentTurn == WHITE) ? BLACK : WHITE;

    Position kingPos;
    bool kingFound = false;

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

bool ChessEngine::isCheckmate() const {
    return  isCheck() && getAllLegalMoves().empty();
}

bool ChessEngine::isStalemate() const {
    return !isCheck() && getAllLegalMoves().empty();
}


ChessBoard ChessEngine::getBoard() const {
    return board;
}


