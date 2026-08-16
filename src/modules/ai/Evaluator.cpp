#include <cctype>
#include <iostream>
#include <string>

#include "../../include/ai/Evaluator.hpp"

using namespace std;

const int Evaluator::pawnPST[8][8] = {
    {  0,  0,  0,  0,  0,  0,  0,  0}, 
    { 50, 50, 50, 50, 50, 50, 50, 50}, 
    { 10, 10, 20, 30, 30, 20, 10, 10}, 
    {  5,  5, 10, 25, 25, 10,  5,  5}, 
    {  0,  0,  0, 20, 20,  0,  0,  0}, 
    {  5, -5,-10,  0,  0,-10, -5,  5}, 
    {  5, 10, 10,-20,-20, 10, 10,  5}, 
    {  0,  0,  0,  0,  0,  0,  0,  0}  
};

const int Evaluator::knightPST[8][8] = {
    {-50,-40,-30,-30,-30,-30,-40,-50},
    {-40,-20,  0,  0,  0,  0,-20,-40},
    {-30,  0, 10, 15, 15, 10,  0,-30},
    {-30,  5, 15, 20, 20, 15,  5,-30},
    {-30,  0, 15, 20, 20, 15,  0,-30},
    {-30,  5, 10, 15, 15, 10,  5,-30},
    {-40,-20,  0,  5,  5,  0,-20,-40},
    {-50,-40,-30,-30,-30,-30,-40,-50}
};

const int Evaluator::bishopPST[8][8] = {
    {-20,-10,-10,-10,-10,-10,-10,-20},
    {-10,  0,  0,  0,  0,  0,  0,-10},
    {-10,  0,  5, 10, 10,  5,  0,-10},
    {-10,  5,  5, 10, 10,  5,  5,-10},
    {-10,  0, 10, 10, 10, 10,  0,-10},
    {-10, 10, 10, 10, 10, 10, 10,-10},
    {-10,  5,  0,  0,  0,  0,  5,-10},
    {-20,-10,-10,-10,-10,-10,-10,-20}
};

const int Evaluator::rookPST[8][8] = {
    {  0,  0,  0,  0,  0,  0,  0,  0}, 
    {  5, 10, 10, 10, 10, 10, 10,  5}, 
    { -5,  0,  0,  0,  0,  0,  0, -5},
    { -5,  0,  0,  0,  0,  0,  0, -5},
    { -5,  0,  0,  0,  0,  0,  0, -5},
    { -5,  0,  0,  0,  0,  0,  0, -5},
    { -5,  0,  0,  0,  0,  0,  0, -5},
    {  0,  0,  0,  5,  5,  0,  0,  0}  
};

const int Evaluator::queenPST[8][8] = {
    {-20,-10,-10, -5, -5,-10,-10,-20},
    {-10,  0,  0,  0,  0,  0,  0,-10},
    {-10,  0,  5,  5,  5,  5,  0,-10},
    { -5,  0,  5,  5,  5,  5,  0, -5},
    {  0,  0,  5,  5,  5,  5,  0, -5},
    {-10,  5,  5,  5,  5,  5,  0,-10},
    {-10,  0,  5,  0,  0,  0,  0,-10},
    {-20,-10,-10, -5, -5,-10,-10,-20}
};


const int Evaluator::kingMiddlePST[8][8] = {
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-20,-30,-30,-40,-40,-30,-30,-20},
    {-10,-20,-20,-20,-20,-20,-20,-10},
    { 20, 20,  0,  0,  0,  0, 20, 20},
    { 20, 30, 10,  0,  0, 10, 30, 20}
};

Evaluator::Evaluator() {
    cout << "Evaluator created successfully!" << endl;
}

Evaluator::~Evaluator() {
    cout << "Evaluator destroyed successfully!" << endl;
}

int Evaluator::getMaterialValue(char piece) const {
    switch (piece) {
        case 'P': return VAL_PAWN;
        case 'N': return VAL_KNIGHT;
        case 'B': return VAL_BISHOP;
        case 'R': return VAL_ROOK;
        case 'Q': return VAL_QUEEN;
        case 'p': return -VAL_PAWN;
        case 'n': return -VAL_KNIGHT;
        case 'b': return -VAL_BISHOP;
        case 'r': return -VAL_ROOK;
        case 'q': return -VAL_QUEEN;
        default: return 0;
    }
}

int Evaluator::getPositionalValue(char piece, char file, char rank) const {
    bool isWhite = isupper(piece);
    char lowerPiece = tolower(piece);

    int col = file - 'a';
    int row;

    if (isWhite) row = '8' - rank;
    else row = rank - '1';

    int score = 0;

    switch (lowerPiece) {
        case 'p': 
            score = pawnPST[row][col];
            break;

        case 'n':
            score = knightPST[row][col];
            break;

        case 'b':
            score = bishopPST[row][col];
            break;

        case 'r':
            score = rookPST[row][col];
            break;

        case 'q':
            score = queenPST[row][col];
            break;

        case 'k':
            score = kingMiddlePST[row][col];
            break;

        default:
            break;
    }
    return isWhite ? score : -score;
}

int Evaluator::evaluate(const ChessBoard& board) const {
    int totalScore = 0;

    for (char file = 'a'; file <= 'h'; file++) {
        for (char rank = '1'; rank <= '8'; rank++) {
            Position pos = createPosition(file, rank);
            string pieceStr = board.getPieceAt(pos);

            if (!pieceStr.empty() && pieceStr != " ") {
                char piece = pieceStr[0];
                totalScore += getMaterialValue(piece);
                totalScore += getPositionalValue(piece, file, rank);
            }
        }
    }
    return totalScore;
}
