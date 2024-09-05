//
//  Piece.cpp
//  Chess
//
//  Created by Landon Mulford on 5/12/24.
//
#include <iostream>
#include "Piece.hpp"

//all virtual functions, should never run
int Piece::getValue(){
   
    return -1;   
}
 vector<vector<int>> Piece::generateMoves(Piece* board[8][8]) const{
    vector<vector<int>> dummy;
    return dummy;
}
char Piece::getType(){
    return 'Z';
}
Piece* Piece::makeCopy(){
    return nullptr;
}

