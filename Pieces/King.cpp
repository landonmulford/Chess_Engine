//
//  King.cpp
//  Chess
//
//  Created by Landon Mulford on 5/12/24.
//

#include "King.hpp"
std::vector<vector<int>> King::generateMoves(Piece* board[8][8]) const{
    vector<vector<int>> result;
    for(int i=-1; i<=1;i++){
          for(int j=-1; j<=1; j++){
            if(posN+i>-1&&posN+i<8&&posL+j>-1&&posL+j<8){
            if(board[posN+i][posL+j]==nullptr||board[posN+i][posL+j]->color!=this->color){
                result.push_back({posN+i,posL+j});
            }
            }
          }
        }
      
    return result;
}
char King::getType(){
    return 'K';
}
Piece* King::makeCopy(){
    King* x=new King(this->color, this->posN, this->posL);
    
    return x;
}
int King::getValue(){return 100;}
