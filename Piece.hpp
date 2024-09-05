//
//  Piece.hpp
//  Chess
//
//  Created by Landon Mulford on 5/12/24.
//

#ifndef Piece_hpp
#define Piece_hpp
using namespace std;
#include <vector>
#include <stdio.h>

class Piece{
public:
    Piece();
    Piece(bool color1, int pos11, int pos21){
        color=color1;
        posN=pos11;
        posL=pos21;
    };
    virtual int getValue();
    bool color;
    int posL;
    int posN;
    virtual Piece* makeCopy();
    virtual char getType();
    virtual vector<vector<int>> generateMoves(Piece* board[8][8]) const;
    
    
    
};

#endif /* Piece_hpp */

