#include <iostream>
#include <vector>
#include <string>
#include <cctype>

#include "../../include/pieces/Queen.hpp"
#include "../../include/core/ChessBoard.hpp"

using namespace std;

// Constructor

Queen::Queen(Color c):Piece(c, (c == WHITE) ? 'Q' : 'q') {
    cout << "Queen created successfully!" << endl;
}

// Destructor

Queen::~Queen() {
    cout << "Queen destroyed successfully!" << endl;
}

// Generates combined orthogonal and diagonal pseudo-legal moves for the Queen.

vector<Move> Queen::getPseudoLegalMoves(const ChessBoard& board, Position currentPos) const {
    vector<Move> moves;

    // All 8 directions (Straight + Diagonal)

    int fileDirections[] = {0, 0, 1, -1, 1, 1, -1, -1};
    int rankDirections[] = {1, -1, 0, 0, 1, -1, 1, -1};

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

    // Raycast in all 8 directions.

    for (int i = 0; i < 8; i++) {
        char targetFile = currentPos.file + fileDirections[i];
        char targetRank = currentPos.rank + rankDirections[i];

        while (isWithinBoard(targetFile, targetRank)) {
            Position targetPos = createPosition(targetFile, targetRank);
            string targetPiece = board.getPieceAt(targetPos);

            // Empty square: Add move and continue.

            if (targetPiece == " ") {
                Move move = createEmptyMove();
                move.start = currentPos;
                move.end = targetPos;
                move.movedPiece = QUEEN;
                moves.push_back(move);
            } else {

                // Opponent piece: Add capture move and stop raycast.

                if (isOpponent(targetPiece)) {
                    Move move = createEmptyMove();
                    move.start = currentPos;
                    move.end = targetPos;
                    move.movedPiece = QUEEN;
                    moves.push_back(move);
                }
                break; // Obstacle encountered
            }
            targetFile += fileDirections[i];
            targetRank += rankDirections[i];
        }
    }
    return moves;
}
