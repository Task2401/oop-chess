#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>

using namespace std;

#include "../../include/core/ChessBoard.hpp"

ChessBoard::ChessBoard()
    :activateColor(COLOR_NONE),
    canCastleKingside{false, false, false},
    canCastleQueenside{false, false, false},
    enPassantTarget(createPosition('-', '-')),
    halfMoveClock(0),
    fullMoveNumber(1)
    {
        setupChessBoard();
        cout << "ChessBoard is created succesfully!" << endl;
    }


ChessBoard::~ChessBoard() {
    cout << "ChessBoard is destroyed succesfully" << endl;
}


void ChessBoard::setupChessBoard() {
    for (int row = 0; row < 8; row++) 
        for (int col = 0; col < 8; col++) 
            chessGrid[row][col] = " ";

    string blackPieces[] = {"r", "n", "b", "q", "k", "b", "n", "r"};
    
    for (int col = 0; col < 8; col++) {
        chessGrid[0][col] = blackPieces[col];
        chessGrid[1][col] = "p";
    }

    string whitePieces[] = {"R", "N", "B", "Q", "K", "B", "N", "R"};

    for (int col = 0; col < 8; col++) {
        chessGrid[6][col] = "P";  
        chessGrid[7][col] = whitePieces[col];
    }

    activateColor = WHITE;

    canCastleKingside[WHITE] = true;
    canCastleQueenside[WHITE] = true;
    canCastleKingside[BLACK] = true;
    canCastleQueenside[BLACK] = true;

    enPassantTarget = createPosition('-', '-');
    halfMoveClock = 0;
    fullMoveNumber = 1;
}

void ChessBoard::printChessBoard() const {
    std::cout << "\033[2J\033[1;1H\n";
    
    for (int row = 0; row < 8; row++) {
        cout << 8 - row << " ";
        for (int col = 0; col < 8; col++) {
            cout << "[" << chessGrid[row][col] << "]";
        } 
        cout << endl;
    }
    cout << "    a  b  c  d  e  f  g  h\n\n";
}

void ChessBoard::clearSquare(const Position& gridPos) {
    chessGrid[getRow(gridPos)][getCol(gridPos)] = " ";
}

void ChessBoard::makeMove(const Move& move) {
    string piece = getPieceAt(move.start);
    string targetPiece = getPieceAt(move.end);

    if (piece == "P" || piece == "p" || targetPiece != " ")
        halfMoveClock = 0;
    else
        halfMoveClock++;

    if (move.isEnPassant) {
        Position capturedPawnPos = createPosition(move.end.file, move.start.rank);
        clearSquare(capturedPawnPos);
    }

    setPieceAt(move.end, piece);
    clearSquare(move.start);

    if(move.isCastling) {
        if(move.end.file == 'g') {
            Position rookFrom = createPosition('h', move.start.rank);
            Position rookTo = createPosition('f', move.start.rank);
            setPieceAt(rookTo, getPieceAt(rookFrom));
            clearSquare(rookFrom);
        }

        else if (move.end.file == 'c') {
            Position rookFrom = createPosition('a', move.start.rank);
            Position rookTo = createPosition('d', move.start.rank);
            setPieceAt(rookTo, getPieceAt(rookFrom));
            clearSquare(rookFrom);
        }
    }

    if(move.promotedTo != ' ' && move.promotedTo != '\0') {
        string promoStr(1, move.promotedTo);
        setPieceAt(move.end, promoStr);
    }

    if (piece == "K") { canCastleKingside[WHITE] = false; canCastleQueenside[WHITE] = false; }
    if (piece == "k") { canCastleKingside[BLACK] = false; canCastleQueenside[BLACK] = false; }
    
    if (piece == "R" && move.start.file == 'h' && move.start.rank == '1') canCastleKingside[WHITE] = false;
    if (piece == "R" && move.start.file == 'a' && move.start.rank == '1') canCastleQueenside[WHITE] = false;
    if (piece == "r" && move.start.file == 'h' && move.start.rank == '8') canCastleKingside[BLACK] = false;
    if (piece == "r" && move.start.file == 'a' && move.start.rank == '8') canCastleQueenside[BLACK] = false;

    if (move.end.file == 'h' && move.end.rank == '1') canCastleKingside[WHITE] = false;
    if (move.end.file == 'a' && move.end.rank == '1') canCastleQueenside[WHITE] = false;
    if (move.end.file == 'h' && move.end.rank == '8') canCastleKingside[BLACK] = false;
    if (move.end.file == 'a' && move.end.rank == '8') canCastleQueenside[BLACK] = false;

    if ((piece == "P" || piece == "p") && abs(move.start.rank - move.end.rank) == 2) {
        char targetRank = (move.start.rank + move.end.rank) / 2;
        enPassantTarget = createPosition(move.start.file, targetRank);
    }else {
        enPassantTarget = createPosition('-', '-');
    }

    if (activateColor == WHITE) {
        activateColor = BLACK;
    }else {
        activateColor = WHITE;
        fullMoveNumber++;
    }
    
}


void ChessBoard::setPieceAt(const Position& piecePos, const string& pieceStr) {
    chessGrid[getRow(piecePos)][getCol(piecePos)] = pieceStr;
}

int ChessBoard::getRow(const Position& gridPos) const{
    return '8' - gridPos.rank;
}

int ChessBoard::getCol(const Position& gridPos) const {
    return gridPos.file - 'a';
}


string ChessBoard::getPieceAt(const Position& piecePos) const {
    return chessGrid[getRow(piecePos)][getCol(piecePos)];
}

Color ChessBoard::getActiveColor() const {
    return activateColor;
}