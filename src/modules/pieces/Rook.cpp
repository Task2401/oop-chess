#include <iostream>
#include <string>
#include <cctype>
#include <vector>

#include "../../include/pieces/Rook.hpp"
#include "../../include/core/ChessBoard.hpp"

using namespace std;

// Constructor

Rook::Rook(Color c):Piece(c, (c == WHITE) ? 'R' : 'r') {
    cout << "Rook created successfully!" << endl;
}

// Destructor

Rook::~Rook() {
    cout << "Rook destroyed successfully!" << endl;
}

// Generates orthogonal (rank/file) pseudo-legal moves for the Rook.

vector<Move> Rook::getPseudoLegalMoves(const ChessBoard& board, Position currentPos) const {
    vector<Move> moves;
    
    // Straight directions: Up, Down, Right, Left.

    int fileDirections[] = {0, 0, 1, -1};
    int rankDirections[] = {1, -1, 0, 0};

    // Helper lambda to check if target piece belongs to opponent.

    auto isOpponent = [&](const string& targetPiece) {
        if (targetPiece == " ") return false;
        if (getColor() == WHITE && islower(targetPiece[0])) return true;
        if (getColor() == BLACK && isupper(targetPiece[0])) return true;
        return false;
    };

    // Helper lambda to check board boundaries.

    auto isWithinBoard = [](char file, char rank) {
        return (file >= 'a' && file <= 'h' && rank >= '1' && rank <= '8');
    };
    
    // Raycast along all 4 straight  directions.

    for (int i = 0; i < 4; i++) {
        char targetFile = currentPos.file + fileDirections[i];
        char targetRank = currentPos.rank + rankDirections[i];
        
        while(isWithinBoard(targetFile, targetRank)) {
            Position targetPos = createPosition(targetFile, targetRank);
            string targetPiece = board.getPieceAt(targetPos);
            
            // Empty square: Add move and continue.

            if (targetPiece == " ") {
                Move move = createEmptyMove();
                move.start = currentPos;
                move.end = targetPos;
                move.movedPiece = ROOK;
                moves.push_back(move);
            } else {
    
                // Opponent piece: Add capture move and stop raycast.

                if (isOpponent(targetPiece)) {
                    Move move = createEmptyMove();
                    move.start = currentPos;
                    move.end = targetPos;
                    move.movedPiece = ROOK;
                    moves.push_back(move);
                }
                break; // Obstacle encountered.
            }
            targetFile += fileDirections[i];
            targetRank += rankDirections[i];
        } 
    }
    return moves;
}


