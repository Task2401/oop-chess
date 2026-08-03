#include <iostream>
#include <vector>
#include <string>
#include <cctype>

#include "../../include/pieces/King.hpp"
#include "../../include/core/ChessBoard.hpp"

using namespace std;

// Constructor

King::King(Color c) : Piece(c, (c == WHITE) ? 'K': 'k') {
    cout << "King created successfully!" << endl;
}

// Destructor

King::~King() {
    cout << "King destroyed successfully!" << endl;
}

// Generates pseudo-legal moves for the King (1-square step in any direction)

vector<Move> King::getPseudoLegalMoves(const ChessBoard& board, Position currentPos) const {
    vector<Move> moves;
    
    // All 8 surrounding adjacent offsets.

    int fileDirections[] = {0, 0, 1, -1, 1, 1, -1, -1};
    int rankDirections[] = {1, -1, 0, 0, 1, -1, 1, -1};

    // Helper lambda to check if target piece belongs to the opponent

    auto isOpponent = [&](const string& targetPiece) {
        if (targetPiece == " ") return false;
        if (getColor() == WHITE && islower(targetPiece[0])) return true;
        if (getColor() == BLACK && isupper(targetPiece[0])) return true;
        return false;
    };

    // Helper lambda to check board boundaries

    auto isWithinBoard= [](char file, char rank) {
        return (file >= 'a' && file <= 'h' && rank >= '1' && rank <= '8');
    };
    
    // Evaluate all 8 adjacent squares

    for (int i = 0; i < 8; i++) {
        char targetFile = currentPos.file + fileDirections[i];
        char targetRank = currentPos.rank + rankDirections[i];

        if (isWithinBoard(targetFile, targetRank)) {
            Position targetPos = createPosition(targetFile, targetRank);
            string targetPiece = board.getPieceAt(targetPos);

            // Valid if target square is empty or contains an enemy piece.

            if (targetPiece == " " || isOpponent(targetPiece)) {
                Move move = createEmptyMove();
                move.start = currentPos;
                move.end = targetPos;
                move.movedPiece = KING;
                moves.push_back(move);
            }
        }
    }
    return moves;
}

