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

//#include <iostream>
#include <stdio.h>

class Piece{
public:
    Piece();
    Piece(bool color1, int pos11, int pos21){
        color=color1;
        posN=pos11;
        posL=pos21;
    };
    //int temp[2];
    virtual int getValue();
    bool color;
    int posL;
    int posN;
    //void displayPiece();
    
    //bool makeMove(int pos_N, int pos_L, Piece[8][8]);
    virtual Piece* makeCopy();
    void addMoves(int pN, int pL);
    void editMoves(Piece[8][8]);
    Piece* moveToBoard(int posN, int posL);
    virtual char getType();
    virtual vector<vector<int>> generateMoves(Piece* board[8][8]) const;
    
    
    
};

#endif /* Piece_hpp */

