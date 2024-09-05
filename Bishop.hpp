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
    
    Bishop(bool color1, int posN, int posL) : Piece(color1,posN,posL){
    }
    int getValue();
    Piece* makeCopy();
    //maybe get rid of legal moves and just return generateMoves for memory reasons
    //for now its void cause of addMoves
    std::vector<vector<int>> generateMoves(Piece* board[8][8]) const;
    char getType();
};
#endif /* Bishop_hpp */
