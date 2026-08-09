#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>

using namespace std;

#include "../../include/core/ChessBoard.hpp"

// Constructor -> Initializes board metadata to default values and triggers setup.

ChessBoard::ChessBoard()
    :activateColor(COLOR_NONE),
    enPassantTarget(createPosition('-', '-')),
    canCastleKingside{false, false, false},
    canCastleQueenside{false, false, false},
    halfMoveClock(0),
    fullMoveNumber(1)
    {
        setupChessBoard();
        cout << "ChessBoard is created succesfully!" << endl;
    }

// Destructor

ChessBoard::~ChessBoard() {
    cout << "ChessBoard is destroyed succesfully" << endl;
}

// Sets up the initial standard chess board layout and game state.

void ChessBoard::setupChessBoard() {
    
    // Clear all grid positions to empty spaces.

    for (int row = 0; row < 8; row++) 
        for (int col = 0; col < 8; col++) 
            chessGrid[row][col] = " ";

    // Place Black major/minor pieces and pawns.

    string blackPieces[] = {"r", "n", "b", "q", "k", "b", "n", "r"};
    
    for (int col = 0; col < 8; col++) {
        chessGrid[0][col] = blackPieces[col];
        chessGrid[1][col] = "p";
    }

    // Place White major/minor pieces and pawns

    string whitePieces[] = {"R", "N", "B", "Q", "K", "B", "N", "R"};

    for (int col = 0; col < 8; col++) {
        chessGrid[6][col] = "P";  
        chessGrid[7][col] = whitePieces[col];
    }

    // Set initial active player and castling rights.

    activateColor = WHITE;
    canCastleKingside[WHITE] = true;
    canCastleQueenside[WHITE] = true;
    canCastleKingside[BLACK] = true;
    canCastleQueenside[BLACK] = true;

    // Reset en passant target and move counters.

    enPassantTarget = createPosition('-', '-');
    halfMoveClock = 0;
    fullMoveNumber = 1;
}

// Clears terminal screen and displays the board to stdout.

void ChessBoard::printChessBoard() const {
    std::cout << "\033[2J\033[1;1H\n"; // ANSI escape sequence to clear screen.
    
    for (int row = 0; row < 8; row++) {
        cout << 8 - row << " "; // Display rank numbers (8 to 1).
        for (int col = 0; col < 8; col++) {
            cout << "[" << chessGrid[row][col] << "]";
        } 
        cout << endl;
    }
    cout << "    a  b  c  d  e  f  g  h\n\n"; // Display file letters
}

// Empties a specific square on the board.

void ChessBoard::clearSquare(const Position& gridPos) {
    chessGrid[getRow(gridPos)][getCol(gridPos)] = " ";
}

// Applies a move to the board, including special move conditions

void ChessBoard::makeMove(const Move& move) {
    string piece = getPieceAt(move.start);
    string targetPiece = getPieceAt(move.end);

    // Reset half-move clock on pawn move or capture: otherwise increment

    if (piece == "P" || piece == "p" || targetPiece != " ")
        halfMoveClock = 0;
    else
        halfMoveClock++;

    // Handle En Passant capture (remove the captured pawn from adjacent rank).

    if (move.isEnPassant) {
        Position capturedPawnPos = createPosition(move.end.file, move.start.rank);
        clearSquare(capturedPawnPos);
    }

    // Move piece to target square and clear origin

    setPieceAt(move.end, piece);
    clearSquare(move.start);

    // Handle Castling (relocate the corresponding Rook).   

    if(move.isCastling) {
        if(move.end.file == 'g') { // Kingside
            Position rookFrom = createPosition('h', move.start.rank);
            Position rookTo = createPosition('f', move.start.rank);
            setPieceAt(rookTo, getPieceAt(rookFrom));
            clearSquare(rookFrom);
        }

        else if (move.end.file == 'c') { //Queenside
            Position rookFrom = createPosition('a', move.start.rank);
            Position rookTo = createPosition('d', move.start.rank);
            setPieceAt(rookTo, getPieceAt(rookFrom));
            clearSquare(rookFrom);
        }
    }

    // Handle Pawn Promotion.

    if (move.isPromotion) {
        string promoStr = "";
        bool isWhite = (piece == "P");

        switch (move.promotedTo) {
            case QUEEN:
                promoStr = isWhite ? "Q" : "q";
                break;

            case ROOK:
                promoStr = isWhite ? "R" : "r";
                break;

            case BISHOP:
                promoStr = isWhite ? "B" : "b";
                break;

            case KNIGHT:
                promoStr = isWhite ? "N" : "n";
                break;

            default:
                promoStr = isWhite ? "Q" : "q";
                break;
        }
        setPieceAt(move.end, promoStr);
    }

    // Revoke castling rights if King moves.

    if (piece == "K") {
        canCastleKingside[WHITE] = false; 
        canCastleQueenside[WHITE] = false; 
    }
    
    if (piece == "k") { 
        canCastleKingside[BLACK] = false; 
        canCastleQueenside[BLACK] = false; 
    }

    // Revoke castling rights if a Rook moves from its initial position.
    
    if (piece == "R" && move.start.file == 'h' && move.start.rank == '1') canCastleKingside[WHITE] = false;
    if (piece == "R" && move.start.file == 'a' && move.start.rank == '1') canCastleQueenside[WHITE] = false;
    if (piece == "r" && move.start.file == 'h' && move.start.rank == '8') canCastleKingside[BLACK] = false;
    if (piece == "r" && move.start.file == 'a' && move.start.rank == '8') canCastleQueenside[BLACK] = false;

    // Revoke castling rights if a Rook is captured at its initial square.

    if (move.end.file == 'h' && move.end.rank == '1') canCastleKingside[WHITE] = false;
    if (move.end.file == 'a' && move.end.rank == '1') canCastleQueenside[WHITE] = false;
    if (move.end.file == 'h' && move.end.rank == '8') canCastleKingside[BLACK] = false;
    if (move.end.file == 'a' && move.end.rank == '8') canCastleQueenside[BLACK] = false;

    // Set target square for en passant if a pawn moves two squares forward.

    if ((piece == "P" || piece == "p") && abs(move.start.rank - move.end.rank) == 2) {
        char targetRank = (move.start.rank + move.end.rank) / 2;
        enPassantTarget = createPosition(move.start.file, targetRank);
    }else {
        enPassantTarget = createPosition('-', '-');
    }

    // Switch active turn and update full-move counter when Black completes turn.

    if (activateColor == WHITE) {
        activateColor = BLACK;
    }else {
        activateColor = WHITE;
        fullMoveNumber++;
    }
    
}

// Sets a piece string at a given board position.

void ChessBoard::setPieceAt(const Position& piecePos, const string& pieceStr) {
    chessGrid[getRow(piecePos)][getCol(piecePos)] = pieceStr;
}

// Converts chess rank character ('1' - '8') to array row index (7 - 0).

int ChessBoard::getRow(const Position& gridPos) const{
    return '8' - gridPos.rank;
}

// Converts chess file character ('a' - 'h') to array column index (0 - 7).

int ChessBoard::getCol(const Position& gridPos) const {
    return gridPos.file - 'a';
}

// Helper methods to access board properties.

int ChessBoard::getHalfMoveClock() const {
    return halfMoveClock;
}

int ChessBoard::getFullMoveNumber() const {
    return fullMoveNumber;
}

bool ChessBoard::getCanCastleKingside(Color color) const {
    return canCastleKingside[color];
}

bool ChessBoard::getCanCastleQueenside(Color color) const {
    return canCastleQueenside[color];
}

string ChessBoard::getPieceAt(const Position& piecePos) const {
    return chessGrid[getRow(piecePos)][getCol(piecePos)];
}

Color ChessBoard::getActiveColor() const {
    return activateColor;
}

Position ChessBoard::getEnPassantTarget() const {
    return enPassantTarget;
} 
