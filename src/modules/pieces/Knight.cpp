#include <iostream>
#include <vector>
#include <string>
#include <cctype>

#include "../../include/core/ChessBoard.hpp"
#include "../../include/pieces/Knight.hpp"


using namespace std;

Knight::Knight(Color c) : Piece(c, (c == WHITE) ? 'N' : 'n') {
    cout << "Knight created succesfully!" << endl;
}

Knight::~Knight() {
    cout << "Knight destroyed succesfully!" << endl;
}

vector<Move> Knight::getPseudoLegalMoves(const ChessBoard& board, Position currentPos) const {
    vector<Move> moves;

    int fileOffsets[] = {1, 2, 2, 1 , -1, -2, -2, -1};
    int rankOffsets[] = {2, 1, -1, -2, -2, -1, 1 , 2};

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
        char targetFile = currentPos.file + fileOffsets[i];
        char targetRank = currentPos.rank + rankOffsets[i];

        if (!isWithinBoard(targetFile, targetRank)) continue;

        Position targetPos = createPosition(targetFile, targetRank);
        string targetPiece = board.getPieceAt(targetPos);

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

