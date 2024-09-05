//
//  King.hpp
//  Chess
//
//  Created by Landon Mulford on 5/12/24.
//

#ifndef King_hpp
#define King_hpp
#include "Piece.hpp"
#include <stdio.h>
#include <vector>
class King: public Piece{
public:
    
    King(bool color1, int posN, int posL) : Piece(color1, posN,posL){
    }
    
    Piece* makeCopy();
    int getValue();
    //maybe get rid of legal moves and just return generateMoves for memory reasons
    //for now its void cause of addMoves
    std::vector<vector<int>> generateMoves(Piece* board[8][8]) const;
    char getType();
};
#endif /* King_hpp */
