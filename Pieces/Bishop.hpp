//
//  Bishop.hpp
//  Chess
//
//  Created by Landon Mulford on 5/12/24.
//

#ifndef Bishop_hpp
#define Bishop_hpp
#include "Piece.hpp"
#include <stdio.h>
class Bishop: public Piece{
public:
    //constructor
    Bishop(bool color1, int posN, int posL) : Piece(color1,posN,posL){
    }
    int getValue();
    //creates copy
    Piece* makeCopy();
    //returns vector of legal moves
    std::vector<vector<int>> generateMoves(Piece* board[8][8]) const;
    //returns type as a char (for displaying)
    char getType();
};
#endif /* Bishop_hpp */
