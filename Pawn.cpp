//
//  Pawn.cpp
//  Chess
//
//  Created by Landon Mulford on 5/12/24.
//

#include "Pawn.hpp"
std::vector<vector<int>> Pawn::generateMoves(Piece* board[8][8]) const{
    //System.out.println(posN+" "+posL);
    
    std::vector<vector<int>> result;
    
    //result.push_back({posN+1, posL});
   
    if(color){
        
    if(board[posN+1][posL]==nullptr){
        //addMoves(posN+1, posL);
          result.push_back({posN+1, posL});
        
        //addMoves need to be changed
        if(posN==1&&(board[posN+2][posL]==nullptr)){
          //addMoves(posN+2, posL);
            result.push_back({posN+2, posL});
        }
      }
        
      if(posL<7&&board[posN+1][posL+1]!=nullptr&&!board[posN+1][posL+1]->color){
          result.push_back({posN+1, posL+1});
        //addMoves(posN+1, posL+1);
      }
      if(posL>0&&board[posN+1][posL-1]!=nullptr&&!board[posN+1][posL-1]->color){
        //addMoves(posN+1, posL-1);
          result.push_back({posN+1, posL-1});
      }
        if(posN==6){
        //adds more moves for different choices for promotions, numbers are dummies
            if(board[posN+1][posL]==nullptr){
                //code for different promotions
                result.push_back({8, posL});
                result.push_back({9, posL});
                result.push_back({10, posL});
                    
                
                //addMoves need to be changed
                if(posN==1&&(board[posN+2][posL]==nullptr)){
                  //addMoves(posN+2, posL);
                result.push_back({8, posL});
                  result.push_back({9, posL});
                  result.push_back({10, posL});
                }
              }
                
              if(posL<7&&board[posN+1][posL+1]!=nullptr&&!board[posN+1][posL+1]->color){
                result.push_back({8, posL});
                result.push_back({9, posL});
                result.push_back({10, posL});
                //addMoves(posN+1, posL+1);
              }
              if(posL>0&&board[posN+1][posL-1]!=nullptr&&!board[posN+1][posL-1]->color){
                //addMoves(posN+1, posL-1);
                result.push_back({8, posL});
                result.push_back({9, posL});
                result.push_back({10, posL});
              }
        }
    }
    else{
      if(board[posN-1][posL]==nullptr){
        //addMoves(posN-1, posL);
          result.push_back({posN-1, posL});
        if(posN==6&&board[posN-2][posL]==nullptr){
          //addMoves(posN-2, posL);
            result.push_back({posN-2, posL});
        }
      }
      if(posL>0&&posN>0&&board[posN-1][posL-1]!=nullptr&&board[posN-1][posL-1]->color){
          result.push_back({posN-1, posL-1});
          //addMoves(posN-1, posL-1);
      }
      if(posL<7&&posN>0&&board[posN-1][posL+1]!=nullptr&&board[posN-1][posL+1]->color){
        //addMoves(posN-1, posL+1);
          result.push_back({posN-1, posL+1});
      }
        if(posN==1){
            if(board[posN-1][posL]==nullptr){
              //addMoves(posN-1, posL);
                result.push_back({-1, posL});
                result.push_back({-2, posL});
                result.push_back({-3, posL});
              if(posN==6&&board[posN-2][posL]==nullptr){
                //addMoves(posN-2, posL);
                result.push_back({-1, posL});
                result.push_back({-2, posL});
                result.push_back({-3, posL});
              }
            }
            if(posL>0&&posN>0&&board[posN-1][posL-1]!=nullptr&&board[posN-1][posL-1]->color){
                result.push_back({-1, posL});
                result.push_back({-2, posL});
                result.push_back({-3, posL});
            }
            if(posL<7&&posN>0&&board[posN-1][posL+1]!=nullptr&&board[posN-1][posL+1]->color){
              //addMoves(posN-1, posL+1);
                result.push_back({-1, posL});
                result.push_back({-2, posL});
                result.push_back({-3, posL});
            }
        }
    }
    
    return result;

    //if(a){editMoves(board);}
    //this needs to be figured out
    //maybe something in the position where if king can be taken it gets removed
    //maybe flag taking king moves somehow
  }
char Pawn::getType(){
    return 'P';
}
Piece* Pawn::makeCopy(){
    Pawn* x=new Pawn(this->color, this->posN, this->posL);
    return x;
}
int Pawn::getValue() {return 1;}

