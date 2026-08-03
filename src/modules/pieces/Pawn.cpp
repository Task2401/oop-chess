#include <iostream>
#include <string>
#include <vector>
#include <cctype>

#include "../../include/pieces/Pawn.hpp"
#include "../../include/core/ChessBoard.hpp"

using namespace std ;

// Constructor

Pawn::Pawn(Color c):Piece(c, (c == WHITE) ? 'P' : 'p') {
    cout << "Pawn created successfully!" << endl;
}

// Destructor

Pawn::~Pawn() {
    cout << "Pawn destroyed successfully!" << endl;
}

// Generates pseudo-legal moves for the pawn (pushes, double-pushes, captures, promotions, en passant)

vector<Move> Pawn::getPseudoLegalMoves(const ChessBoard& board, Position currentPos) const {
    vector<Move> moves;

    // Movement direction (+1 for White moving up, -1 for Black moving down).

    int direction = (getColor() == WHITE) ? 1 : -1;
    char startingRank = (getColor() == WHITE) ? '2' : '7';
    char promotionRank = (getColor() == WHITE) ? '8' : '1';
    
    // Forward 1-Square Step.

    Position forwardOne = createPosition(currentPos.file, currentPos.rank + direction);
    
    if (board.getPieceAt(forwardOne) == " ") {

        // Handle Pawn Promotion on single forward push.

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
            
            // Forward 2-Square Step (allowed only from starting rank if path is clear).

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
    
    // Helper lambda to check if target piece belongs to opponent.

    auto isOpponent = [&](const string& targetPiece) {
        if (targetPiece == " ") return false;
        if (getColor() == WHITE && islower(targetPiece[0])) return true;
        if (getColor() == BLACK && isupper(targetPiece[0])) return true;
        return false;
    };

    Position enPassantTarget = board.getEnPassantTarget();

    // Diagonal Capture Left (File -1).

    if (currentPos.file > 'a') {
        Position captureLeft = createPosition(currentPos.file - 1, currentPos.rank + direction);
        string targetPiece = board.getPieceAt(captureLeft);
        
        bool isEnPassant = (captureLeft.file == enPassantTarget.file && captureLeft.rank == enPassantTarget.rank);
        
        if (isOpponent(targetPiece) || isEnPassant) {

            // Check for capture resulting in promotion.            
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
    
    // Diagonal Capture Right (File + 1).

    if (currentPos.file < 'h') {
        Position captureRight = createPosition(currentPos.file + 1, currentPos.rank + direction);
        string targetPiece = board.getPieceAt(captureRight);
        bool isEnPassant = (captureRight.file == enPassantTarget.file && captureRight.rank == enPassantTarget.rank);
        
        if (isOpponent(targetPiece) || isEnPassant) {
    
            // Check for capture resulting in promotion.

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

