#include <sstream>
#include <cctype>

#include "../../include/utils/FEN.hpp"

using namespace std;

FEN fenParser(const string& fenString) {
    FEN data;

    for (int gridRow = 0; gridRow < 8; gridRow++) 
        for (int gridCol = 0; gridCol < 8; gridCol++)
            data.grid[gridRow][gridCol] = " ";

    data.canCastleKingside[WHITE] = false;
    data.canCastleQueenside[WHITE] = false;
    data.canCastleKingside[BLACK] = false;
    data.canCastleQueenside[BLACK] = false;

    istringstream iss(fenString);
    string placement, activeColor, castling, enPassant, halfMove, fullMove;

    iss >> placement >> activeColor >> castling >> enPassant >> halfMove >> fullMove;

    int gridRow;
    int gridCol;

    gridRow = gridCol = 0;

    for (char ch : placement) {
        if (ch == '/') {
            gridRow++;
            gridCol = 0;
        }
        else if (isdigit(ch))
            gridCol += (ch - '0');
        else {
            data.grid[gridRow][gridCol] = string(1, ch);
            gridCol++;
        }
    }

    data.activateColor = (activeColor == "w") ? WHITE : BLACK;

    if (castling != "-") {
        for (char ch : castling) {
            switch(ch) {
                case 'K':
                    data.canCastleKingside[WHITE] = true;
                    break;
                
                case 'Q':
                    data.canCastleQueenside[WHITE] = true;
                    break;
                
                case 'k':
                    data.canCastleKingside[BLACK] = true;
                    break;
                
                case 'q':
                    data.canCastleQueenside[BLACK] = true;
                    break;
            }
        }
    }

    if (enPassant == "-" || enPassant.empty()) 
        data.enPassantTarget = createPosition('-', '-');
    else
     data.enPassantTarget = createPosition(enPassant[0], enPassant[1]);

    data.halfMoveClock = halfMove.empty() ? 0 : stoi(halfMove);
    data.fullMoveNumber = fullMove.empty() ? 1 : stoi(fullMove);

    return data;
}

string fenGenerator(const ChessBoard& board) {
    stringstream fen;

    for (char rank = '8'; rank >= '1'; rank--) {
        int emptyCount = 0;
        for (char file = 'a'; file <= 'h'; file ++) {
            string piece = board.getPieceAt(createPosition(file, rank));
            
            if (piece == " ") emptyCount++;

            else {
                if (emptyCount > 0) {
                    fen << emptyCount;
                    emptyCount = 0;
                }
                fen << piece;
            }
        }
        if ( emptyCount > 0) fen << emptyCount;
        if (rank > '1') fen << "/";
    }

    fen << " " << (board.getActiveColor() == WHITE ? "w" : "b");

    string castling = "";

    if (board.getCanCastleKingside(WHITE)) castling += "K";
    if (board.getCanCastleQueenside(WHITE)) castling += "Q";
    if (board.getCanCastleKingside(BLACK)) castling += "k";
    if (board.getCanCastleQueenside(BLACK)) castling += "q";

    fen << " " << (castling.empty() ? "-" : castling);
    
    fen << " ";
    
    Position enPassant = board.getEnPassantTarget();

    if (enPassant.file == '-' || enPassant.rank == '-') fen << "-";
    else fen << enPassant.file << enPassant.rank;

    fen << " " << board.getHalfMoveClock();
    fen << " " << board.getFullMoveNumber();

    return fen.str();
}

