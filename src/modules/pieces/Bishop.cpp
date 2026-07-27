#include <iostream>
#include <vector>
#include <string>
#include <cctype>

#include "../../include/core/ChessBoard.hpp"
#include "../../include/pieces/Bishop.hpp"

using namespace std;

Bishop::Bishop(Color c):Piece(c, (c == WHITE) ? 'B': 'b') {
    cout << "Bishop created succesfully!" << endl;
}

Bishop::~Bishop() {
    cout << "Bishop destroyed succesfully!" << endl;
}

vector<Move> Bishop::getPseudoLegalMoves(const ChessBoard& board, Position currentPos) const {
    vector<Move> moves;

    int fileDirections[] = {1, 1, -1, -1};
    int rankDirections[] = {1, -1, 1 ,-1};

    auto isOpponent = [&](const string& targetPiece) {
        if (targetPiece == " ") return false;
        if (getColor() == WHITE && islower(targetPiece[0])) return true;

        return false;
    };

    auto isWithinBoard = [](char file, char rank) {
        return (file >= 'a' && file <= 'h' && rank >= '1' && rank <= '8');
    };

    for (int i = 0; i < 4; i++) {
        char targetFile = currentPos.file + fileDirections[i];
        char targetRank = currentPos.rank + rankDirections[i];

        while (isWithinBoard(targetFile, targetRank)) {
            Position targetPos = createPosition(targetFile, targetRank);
            string targetPiece = board.getPieceAt(targetPos);
            
            if (targetPiece == " ") {
                Move move = createEmptyMove();
                move.start = currentPos;
                move.end = targetPos;
                move.movedPiece = BISHOP;
                moves.push_back(move);
            } else {
                if (isOpponent(targetPiece)) {
                    Move move = createEmptyMove();
                    move.start = currentPos;
                    move.end = targetPos;
                    move.movedPiece = BISHOP;
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
