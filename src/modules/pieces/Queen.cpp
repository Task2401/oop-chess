#include <iostream>
#include <vector>
#include <string>
#include <cctype>

#include "../../include/core/ChessBoard.hpp"
#include "../../include/pieces/Queen.hpp"

using namespace std;

Queen::Queen(Color c):Piece(c, (c == WHITE) ? 'Q' : 'q') {
    cout << "Queen created succesfully!" << endl;
}

Queen::~Queen() {
    cout << "Queen destroyed succesfully!" << endl;
}

vector<Move> Queen::getPseudoLegalMoves(const ChessBoard& board, Position currentPos) const {
    vector<Move> moves;

    int fileDirections[] = {0, 0, 1, -1, 1, 1, -1, -1};
    int rankDirections[] = {1, -1, 0, 0, 1, -1, 1, -1};

    auto isOpponent = [&](const string& targetPiece) {
        if (targetPiece == " ") return false;
        if (getColor() == WHITE && islower(targetPiece[0])) return true;
        if (getColor() == BLACK && isupper(targetPiece[0])) return true;
        return false;
    };

    auto isWithinBoard = [](char file, char rank) {
        return (file >= 'a' && file <= 'h' && rank >= '1' && rank <= '8');
    };

    for (int i = 0; i < 8; i++) {
        char targetFile = currentPos.file + fileDirections[i];
        char targetRank = currentPos.rank + rankDirections[i];

        while (isWithinBoard(targetFile, targetRank)) {
            Position targetPos = createPosition(targetFile, targetRank);
            string targetPiece = board.getPieceAt(targetPos);

            if (targetPiece == " ") {
                Move move = createEmptyMove();
                move.start = currentPos;
                move.end = targetPos;
                move.movedPiece = QUEEN;
                moves.push_back(move);
            } else {
                if (isOpponent(targetPiece)) {
                    Move move = createEmptyMove();
                    move.start = currentPos;
                    move.end = targetPos;
                    move.movedPiece = QUEEN;
                    moves.push_back(move);
                }
                break;
            }
            targetFile += fileDirections[i];
            targetRank += rankDirections[i];
        }
    }
    return moves;
}
