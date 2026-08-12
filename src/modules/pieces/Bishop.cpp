#include <iostream>
#include <vector>
#include <string>
#include <cctype>

#include "../../include/pieces/Bishop.hpp"
#include "../../include/core/ChessBoard.hpp"


using namespace std;

// Constructor

Bishop::Bishop(Color c):Piece(c, (c == WHITE) ? 'B': 'b') {
    cout << "Bishop created successfully!" << endl;
}

// Destructor

Bishop::~Bishop() {
    cout << "Bishop destroyed successfully!" << endl;
}

// Generates diagonal pseudo-legal moves for the bishop.

vector<Move> Bishop::getPseudoLegalMoves(const ChessBoard& board, Position currentPos) const {
    vector<Move> moves;

    // Diagonal raycast directions: Up-Right, Down-Right, Up-Left Down-Left

    int fileDirections[] = {1, 1, -1, -1};
    int rankDirections[] = {1, -1, 1 ,-1};

    // Helper lambda to check if a target piece belongs to the opponent.

    auto isOpponent = [&](const string& targetPiece) {
        if (targetPiece == " ") return false;
        if (getColor() == WHITE && islower(targetPiece[0])) return true;
        if (getColor() == BLACK && isupper(targetPiece[0])) return true;
        return false;
    };

    // Helper lambda to check board boundaries

    auto isWithinBoard = [](char file, char rank) {
        return (file >= 'a' && file <= 'h' && rank >= '1' && rank <= '8');
    };

    // Raycast along all 4 diagonal directions.

    for (int i = 0; i < 4; i++) {
        char targetFile = currentPos.file + fileDirections[i];
        char targetRank = currentPos.rank + rankDirections[i];

        while (isWithinBoard(targetFile, targetRank)) {
            Position targetPos = createPosition(targetFile, targetRank);
            string targetPiece = board.getPieceAt(targetPos);
            
            // Empty square: Add move and continue raycasting

            if (targetPiece == " ") {
                Move move = createEmptyMove();
                move.start = currentPos;
                move.end = targetPos;
                move.movedPiece = BISHOP;
                moves.push_back(move);
            } else {
    
                // Opponent piece: Add capture move and stop raycasting.

                if (isOpponent(targetPiece)) {
                    Move move = createEmptyMove();
                    move.start = currentPos;
                    move.end = targetPos;
                    move.movedPiece = BISHOP;
                    moves.push_back(move); 
                }
                break; // Friendly piece or opponent blocks further raycast.
            }
            targetFile += fileDirections[i];
            targetRank += rankDirections[i];
        }
    }
    return moves;
}
