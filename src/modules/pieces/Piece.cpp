#include <iostream>
#include <cstdlib>

using namespace std;

#include "../../include/pieces/Piece.hpp"

Piece::Piece(Color c, char s):color(c), symbol(s) {
    cout << "Piece -> " << symbol << "created succesfully!" << endl;

}


Color Piece::getColor() const {
    return color;
}

char Piece::getSymbol() const {
    return symbol;
}


