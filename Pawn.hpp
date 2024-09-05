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
    
    Pawn(bool color1, int posN, int posL) : Piece(color1,posN,posL){
    };
    Piece* makeCopy();
    int getValue();
    char getType();
    //maybe get rid of legal moves and just return generateMoves for memory reasons
    //for now its void cause of addMoves
    std::vector<vector<int>> generateMoves(Piece* board[8][8]) const;
        
};
#endif /* Pawn_hpp */
