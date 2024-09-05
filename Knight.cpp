//
//  Knight.cpp
//  Chess
//
//  Created by Landon Mulford on 5/12/24.
//

#include "Knight.hpp"
std::vector<vector<int>> Knight::generateMoves(Piece* board[8][8]) const{
    vector<vector<int>> result;
    if(posN+2<8&&posL+1<8){
          if(board[posN+2][posL+1]==nullptr||board[posN+2][posL+1]->color!=this->color){
            //addMoves(posN+2,posL+1);
              result.push_back({posN+2, posL+1});
          }
        }
        if(posN+1<8&&posL+2<8){
          if(board[posN+1][posL+2]==nullptr||board[posN+1][posL+2]->color!=this->color){
            //addMoves(posN+1,posL+2);
              result.push_back({posN+1, posL+2});
          }
        }
        if(posN-2>-1&&posL+1<8){
          if(board[posN-2][posL+1]==nullptr||board[posN-2][posL+1]->color!=this->color){
            //addMoves(posN-2,posL+1);
            result.push_back({posN-2, posL+1});
          }
        }
        if(posN-1>-1&&posL+2<8){
          if(board[posN-1][posL+2]==nullptr||board[posN-1][posL+2]->color!=this->color){
            //addMoves(posN-1,posL+2);
            result.push_back({posN-1, posL+2});
          }
        }
        if(posN+2<8&&posL-1>-1){
          if(board[posN+2][posL-1]==nullptr||board[posN+2][posL-1]->color!=this->color){
            //addMoves(posN+2,posL-1);
              result.push_back({posN+2, posL-1});
          }
        }
        if(posN-1>-1&&posL+2<8){
          if(board[posN-1][posL+2]==nullptr||board[posN-1][posL+2]->color!=this->color){
            //addMoves(posN-1,posL+2);
              result.push_back({posN-1, posL+2});
          }
        }
        if(posN-2>-1&&posL-1>-1){
          if(board[posN-2][posL-1]==nullptr||board[posN-2][posL-1]->color!=this->color){
            //addMoves(posN-2,posL-1);
              result.push_back({posN-2, posL-1});
          }
        }
        if(posN-1>-1&&posL-2>-1){
          if(board[posN-1][posL-2]==nullptr||board[posN-1][posL-2]->color!=this->color){
            //addMoves(posN-1,posL-2);
              result.push_back({posN-1, posL-2});
          }
        }
        //if(a){editMoves(board);}
    return result;
      }
    

char Knight::getType(){
    return 'N';
}
Piece* Knight::makeCopy(){
    Knight* x=new Knight(this->color, this->posN, this->posL);
    
    return x;
}
int Knight::getValue() {return 3;}

