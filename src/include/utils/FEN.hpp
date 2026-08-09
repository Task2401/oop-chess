#ifndef FEN_HPP
#define FEN_HPP

#include <string>

#include "../core/Common.hpp"
#include "../core/ChessBoard.hpp"

struct FEN {
    std::string grid[8][8];
    Color activateColor;
    bool canCastleKingside[3];
    bool canCastleQueenside[3];
    Position enPassantTarget;
    int halfMoveClock;
    int fullMoveNumber;
};

FEN fenParser(const std::string& fenString);
std::string fenGenerator(const ChessBoard& board);
 
#endif  // FEN_HPP
