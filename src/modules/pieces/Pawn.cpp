#include <iostream>
#include <string>
#include <vector>
#include <cctype>

#include "../../include/pieces/Pawn.hpp"
#include "../../include/core/ChessBoard.hpp"

using namespace std ;

Pawn::Pawn(Color c):Piece(c, (c == WHITE) ? 'P' : 'p') {
    cout << "Pawn created succesfully!" << endl;
}

Pawn::~Pawn() {
    cout << "Pawn destroyed succesfully!" << endl;
}

vector<Move> Pawn::getPseudoLegalMoves(const ChessBoard& board, Position currentPos) const {
    vector<Move> moves;

    int direction = (getColor() == WHITE) ? 1 : -1;
    char startingRank = (getColor() == WHITE) ? '2' : '7';
    char promotionRank = (getColor() == WHITE) ? '8' : '1';
    
    Position forwardOne = createPosition(currentPos.file, currentPos.rank + direction);
    
    if (board.getPieceAt(forwardOne) == " ") {
        if (forwardOne.rank == promotionRank) {
            PieceType promotions[] = {QUEEN, ROOK, BISHOP, KNIGHT};
            for (PieceType p : promotions) {
                Move move = createEmptyMove();
                move.start = currentPos;
                move.end = forwardOne;
                move.movedPiece = PAWN;
                move.promotedTo = p;
                move.isPromotion = true;
                moves.push_back(move);
            }
        } else {
            Move move = createEmptyMove();
            move.start = currentPos;
            move.end = forwardOne;
            move.movedPiece = PAWN;
            moves.push_back(move);
            
            if (currentPos.rank == startingRank) {
                Position forwardTwo = createPosition(currentPos.file, currentPos.rank + 2 * direction);
                if (board.getPieceAt(forwardTwo) == " ") {
                    Move move2 = createEmptyMove();
                    move2.start = currentPos;
                    move2.end = forwardTwo;
                    move2.movedPiece = PAWN;
                    moves.push_back(move2);
                }
            }
        }
    }
    
    auto isOpponent = [&](const string& targetPiece) {
        if (targetPiece == " ") return false;
        if (getColor() == WHITE && islower(targetPiece[0])) return true;
        if (getColor() == BLACK && isupper(targetPiece[0])) return true;
        return false;
    };

    Position enPassantTarget = board.getEnPassantTarget();

    if (currentPos.file > 'a') {
        Position captureLeft = createPosition(currentPos.file - 1, currentPos.rank + direction);
        string targetPiece = board.getPieceAt(captureLeft);
        
        bool isEnPassant = (captureLeft.file == enPassantTarget.file && captureLeft.rank == enPassantTarget.rank);
        
        if (isOpponent(targetPiece) || isEnPassant) {
            if (captureLeft.rank == promotionRank) {
                PieceType promotions[] = {QUEEN, ROOK, BISHOP, KNIGHT};
                for (PieceType p : promotions) {
                    Move move = createEmptyMove();
                    move.start = currentPos;
                    move.end = captureLeft;
                    move.movedPiece = PAWN;
                    move.promotedTo = p;
                    move.isPromotion = true;
                    move.isEnPassant = isEnPassant;
                    moves.push_back(move);
                }
            } else {
                Move move = createEmptyMove();
                move.start = currentPos;
                move.end = captureLeft;
                move.movedPiece = PAWN;
                move.isEnPassant = isEnPassant;
                moves.push_back(move);
            }
        }
    }
    
    if (currentPos.file < 'h') {
        Position captureRight = createPosition(currentPos.file + 1, currentPos.rank + direction);
        string targetPiece = board.getPieceAt(captureRight);
        bool isEnPassant = (captureRight.file == enPassantTarget.file && captureRight.rank == enPassantTarget.rank);
        
        if (isOpponent(targetPiece) || isEnPassant) {
            if (captureRight.rank == promotionRank) {
                PieceType promotions[] = {QUEEN, ROOK, BISHOP, KNIGHT};
                for (PieceType p : promotions) {
                    Move move = createEmptyMove();
                    move.start = currentPos;
                    move.end = captureRight;
                    move.movedPiece = PAWN;
                    move.promotedTo = p;
                    move.isPromotion = true;
                    move.isEnPassant = isEnPassant;
                    moves.push_back(move);
                }
            } else {
                Move move = createEmptyMove();
                move.start = currentPos;
                move.end = captureRight;
                move.movedPiece = PAWN;
                move.isEnPassant = isEnPassant;
                moves.push_back(move);
            }
        }
    }
    return moves;
}   

