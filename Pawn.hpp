//
//  Pawn.hpp
//  Chess
//
//  Created by Landon Mulford on 5/12/24.
//

#ifndef Pawn_hpp
#define Pawn_hpp
#include "Piece.hpp"
#include <vector>
#include <iostream>
#include <stdio.h>
class Pawn: public Piece{
public:
    
    //constructor
    Pawn(bool color1, int posN, int posL) : Piece(color1, posN,posL){
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
#endif /* Pawn_hpp */
