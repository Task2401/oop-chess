#include <iostream>
#include <vector>
#include <string>
#include <cctype>

#include "../../include/pieces/King.hpp"
#include "../../include/core/ChessBoard.hpp"

using namespace std;

King::King(Color c) : Piece(c, (c == WHITE) ? 'K': 'k') {
    cout << "King created succesfully!" << endl;
}

King::~King() {
    cout << "King destroyed succesfully!" << endl;
}

vector<Move> King::getPseudoLegalMoves(const ChessBoard& board, Position currentPos) const {
    vector<Move> moves;
    
    int fileDirections[] = {0, 0, 1, -1, 1, 1, -1, -1};
    int rankDirections[] = {1, -1, 0, 0, 1, -1, 1, -1};

    auto isOpponent = [&](const string& targetPiece) {
        if (targetPiece == " ") return false;
        if (getColor() == WHITE && islower(targetPiece[0])) return true;
        if (getColor() == BLACK && isupper(targetPiece[0])) return true;
        return false;
    };

    auto isWithinBoard= [](char file, char rank) {
        return (file >= 'a' && file <= 'h' && rank >= '1' && rank <= '8');
    };
    
    for (int i = 0; i < 8; i++) {
        char targetFile = currentPos.file + fileDirections[i];
        char targetRank = currentPos.rank + rankDirections[i];

        if (isWithinBoard(targetFile, targetRank)) {
            Position targetPos = createPosition(targetFile, targetRank);
            string targetPiece = board.getPieceAt(targetPos);

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

