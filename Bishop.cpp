//
//  Bishop.cpp
//  Chess
//
//  Created by Landon Mulford on 5/12/24.
//

#include "Bishop.hpp"
//returns letter for Tyoe, used in output
char Bishop::getType(){
    return 'B';
}
//makes copy of input piece
Piece* Bishop::makeCopy(){
    Bishop* x=new Bishop(this->color, this->posN, this->posL);
   
    return x;
}
//returns vector with all of the locations the piece can move
std::vector<vector<int>> Bishop::generateMoves(Piece* board[8][8])const {
    std::vector<vector<int>> result;
    int i=1;
    while(posN+i<8&&posL+i<8){
      if(board[posN+i][posL+i]==nullptr){
          result.push_back({posN+i, posL+i});
        i++;
      }
      else if(board[posN+i][posL+i]->color!=this->color){
          result.push_back({posN+i, posL+i});
        break;
      }
      else{break;}
    }
    i=1;
    while(posN+i<8&&posL-i>=0){
      if(board[posN+i][posL-i]==nullptr){
          result.push_back({posN+i, posL-i});
        i++;
      }
      else if(board[posN+i][posL-i]->color!=this->color){
          result.push_back({posN+i, posL-i});
        break;
      }
      else{break;}
    }
    i=1;
    while(posN-i>=0&&posL+i<8){
      if(board[posN-i][posL+i]==nullptr){
        result.push_back({posN-i, posL+i});
        i++;
      }
      else if(board[posN-i][posL+i]->color!=this->color){
          result.push_back({posN-i, posL+i});
        break;
      }
      else{break;}
    }
    i=1;
    while(posN-i>=0&&posL-i>=0){
      if(board[posN-i][posL-i]==nullptr){
          result.push_back({posN-i, posL-i});
        i++;
      }
      else if(board[posN-i][posL-i]->color!=this->color){
          result.push_back({posN-i, posL-i});
        break;
      }
      else{break;}
    }
    return result;
  }
//returns material value
int Bishop::getValue(){return 3;}
