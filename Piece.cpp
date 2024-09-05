//
//  Piece.cpp
//  Chess
//
//  Created by Landon Mulford on 5/12/24.
//
#include <iostream>
#include "Piece.hpp"

void Piece::addMoves(int pN, int pL){
   //temp[0]=pN;
    //temp[1]=pL;
        //System.out.println("["+temp[0]+" "+temp[1]+"]");
    //legalMoves.add(temp);
      
}
int Piece::getValue(){
    /*if(type=="Pawn"){return 1;}
    if(type=="Knight"||type=="Bishop"){return 3;}
    if(type=="Rook"){return 5;}
    if(type=="Queen"){return 9;}
    if(type=="King"){return 15;}*/
    return -1;
      
}
 vector<vector<int>> Piece::generateMoves(Piece* board[8][8]) const{
    
    cout<<"This is running the Piece version of generateMoves";
    vector<vector<int>> cheers;
    return cheers;
}
char Piece::getType(){
    return 'L';
}
Piece* Piece::makeCopy(){
    return nullptr;
}

