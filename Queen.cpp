//
//  Queen.cpp
//  Chess
//
//  Created by Landon Mulford on 5/12/24.
//

#include "Queen.hpp"
std::vector<vector<int>> Queen::generateMoves(Piece* board[8][8]) const{
    vector<vector<int>> result;
    int i=1;
        while(posN+i<8){
          if(board[posN+i][posL]==nullptr){
            //addMoves(posN+i, posL);
              result.push_back({posN+i, posL});
            i++;
          }
          else if(board[posN+i][posL]->color!=this->color){
            //addMoves(posN+i, posL);
            result.push_back({posN+i, posL});
            break;
          }
          else{break;}
        }
        i=1;
        while(posN-i>-1){
          if(board[posN-i][posL]==nullptr){
            //addMoves(posN-i, posL);
              result.push_back({posN-i, posL});
            i++;
          }
          else if(board[posN-i][posL]->color!=this->color){
            //addMoves(posN-i, posL);
              result.push_back({posN-i, posL});
            break;
          }
          else{break;}
        }
        i=1;
        while(posL+i<8){
          if(board[posN][posL+i]==nullptr){
            //addMoves(posN, posL+i);
              result.push_back({posN, posL+i});
            i++;
          }
          else if(board[posN][posL+i]->color!=this->color){
            //addMoves(posN, posL+i);
              result.push_back({posN, posL+i});
            break;
          }
          else{break;}
        }
        i=1;
        while(posL-i>-1){
          if(board[posN][posL-i]==nullptr){
            //addMoves(posN, posL-i);
            result.push_back({posN, posL-i});
            i++;
          }
          else if(board[posN][posL-i]->color!=this->color){
            //addMoves(posN, posL-i);
            result.push_back({posN, posL-i});
            break;
          }
          else{break;}
        }
        i=1;
        while(posN+i<8&&posL+i<8){
          if(board[posN+i][posL+i]==nullptr){
            //addMoves(posN+i, posL+i);
            result.push_back({posN+i, posL+i});
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
          //System.out.println("Hi");
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
char Queen::getType(){
    return 'Q';
}
Piece* Queen::makeCopy(){
    Queen* x=new Queen(this->color, this->posN, this->posL);
    
    return x;
}
int Queen::getValue(){return 9;}
