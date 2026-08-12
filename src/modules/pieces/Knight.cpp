#include <iostream>
#include <vector>
#include <string>
#include <cctype>

#include "../../include/pieces/Knight.hpp"
#include "../../include/core/ChessBoard.hpp"

using namespace std;

// Constructor

Knight::Knight(Color c) : Piece(c, (c == WHITE) ? 'N' : 'n') {
    cout << "Knight created successfully!" << endl;
}

// Destructor

Knight::~Knight() {
    cout << "Knight destroyed successfully!" << endl;
}

// Generates L-shaped pseudo-legal moves for the Knight.

vector<Move> Knight::getPseudoLegalMoves(const ChessBoard& board, Position currentPos) const {
    vector<Move> moves;

    // All 8 potential L-shaped offsets.

    int fileOffsets[] = {1, 2, 2, 1 , -1, -2, -2, -1};
    int rankOffsets[] = {2, 1, -1, -2, -2, -1, 1 , 2};

    // Helper lambda to check if target piece belongs to opponent

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
    
    // Evaluates all 8 possible Knight jumps.

    for (int i = 0; i < 8; i++) {
        char targetFile = currentPos.file + fileOffsets[i];
        char targetRank = currentPos.rank + rankOffsets[i];

        if (!isWithinBoard(targetFile, targetRank)) continue;

        Position targetPos = createPosition(targetFile, targetRank);
        string targetPiece = board.getPieceAt(targetPos);

        // Knight can jump over pieces: valid if square is empty or has an enemey.

        if (targetPiece == " " || isOpponent(targetPiece)) {
            Move move = createEmptyMove();
            move.start = currentPos;
            move.end = targetPos;
            move.movedPiece = KNIGHT;
            moves.push_back(move);
        }
    }
    return moves;
}

