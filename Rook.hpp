//
//  Rook.hpp
//  Chess
//
//  Created by Landon Mulford on 5/12/24.
//

#ifndef Rook_hpp
#define Rook_hpp
#include "Piece.hpp"
#include <stdio.h>
class Rook: public Piece{
public:
     //constructor
    Rook(bool color1, int posN, int posL) : Piece(color1, posN,posL){
    }
    //creates copy
    Piece* makeCopy();
    //returns material value
    int getValue();
    //returns vector of legal moves
    std::vector<vector<int>> generateMoves(Piece* board[8][8]) const;
    //returns type as a char (for displaying)
    char getType();
};
#endif /* Rook_hpp */
