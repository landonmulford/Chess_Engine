//
//  Bishop.cpp
//  Chess
//
//  Created by Landon Mulford on 5/12/24.
//

#include "Bishop.hpp"

char Bishop::getType(){
    return 'B';
}
Piece* Bishop::makeCopy(){
    Bishop* x=new Bishop(this->color, this->posN, this->posL);
   
    return x;
}
std::vector<vector<int>> Bishop::generateMoves(Piece* board[8][8])const {
    //System.out.println(posN+" "+posL);
    std::vector<vector<int>> result;
    int i=1;
    while(posN+i<8&&posL+i<8){
      if(board[posN+i][posL+i]==nullptr){
          result.push_back({posN+i, posL+i});
        //addMoves(posN+i, posL+i);
        i++;
      }
      else if(board[posN+i][posL+i]->color!=this->color){
        //addMoves(posN+i, posL+i);
          result.push_back({posN+i, posL+i});
        break;
      }
      else{break;}
    }
    i=1;
    while(posN+i<8&&posL-i>=0){
      if(board[posN+i][posL-i]==nullptr){
        //addMoves(posN+i, posL-i);
          result.push_back({posN+i, posL-i});
        i++;
      }
      else if(board[posN+i][posL-i]->color!=this->color){
        //addMoves(posN+i, posL-i);
          result.push_back({posN+i, posL-i});
        break;
      }
      else{break;}
    }
    i=1;
    while(posN-i>=0&&posL+i<8){
      if(board[posN-i][posL+i]==nullptr){
        //addMoves(posN-i, posL+i);
        result.push_back({posN-i, posL+i});
        i++;
      }
      else if(board[posN-i][posL+i]->color!=this->color){
        //addMoves(posN-i, posL+i);
          result.push_back({posN-i, posL+i});
        break;
      }
      else{break;}
    }
    i=1;
    while(posN-i>=0&&posL-i>=0){
      if(board[posN-i][posL-i]==nullptr){
        //addMoves(posN-i, posL-i);
          result.push_back({posN-i, posL-i});
        i++;
      }
      else if(board[posN-i][posL-i]->color!=this->color){
        //addMoves(posN-i, posL-i);
          result.push_back({posN-i, posL-i});
        break;
      }
      else{break;}
    }
    //if(a){editMoves(board);}
    return result;
  }
int Bishop::getValue(){return 3;}
