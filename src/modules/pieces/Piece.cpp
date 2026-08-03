#include <iostream>
#include <cstdlib>

#include "../../include/pieces/Piece.hpp"

using namespace std;

// Constructor: Initializes base properties (color and symbol)

Piece::Piece(Color c, char s):color(c), symbol(s) {
    cout << "Piece -> " << symbol << " created successfully!" << endl;
}

// Getters

Color Piece::getColor() const {
    return color;
}

char Piece::getSymbol() const {
    return symbol;
}


