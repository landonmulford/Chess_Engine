//
//  Rook.cpp
//  Chess
//
//  Created by Landon Mulford on 5/12/24.
//

#include "Rook.hpp"
std::vector<vector<int>> Rook::generateMoves(Piece* board[8][8]) const{
    vector<vector<int>> result;
    int i=1;
        while(posN+i<8){
          if(board[posN+i][posL]==nullptr){
          
              result.push_back({posN+i, posL});
            i++;
          }
          else if(board[posN+i][posL]->color!=this->color){
            
            result.push_back({posN+i, posL});
            break;
          }
          else{break;}
        }
        i=1;
        while(posN-i>-1){
          if(board[posN-i][posL]==nullptr){
           
              result.push_back({posN-i, posL});
            i++;
          }
          else if(board[posN-i][posL]->color!=this->color){
            
              result.push_back({posN-i, posL});
            break;
          }
          else{break;}
        }
        i=1;
        while(posL+i<8){
          if(board[posN][posL+i]==nullptr){
         
              result.push_back({posN, posL+i});
            i++;
          }
          else if(board[posN][posL+i]->color!=this->color){
            
              result.push_back({posN, posL+i});
            break;
          }
          else{break;}
        }
        i=1;
        while(posL-i>-1){
          if(board[posN][posL-i]==nullptr){
      
            result.push_back({posN, posL-i});
            i++;
          }
          else if(board[posN][posL-i]->color!=this->color){
          
            result.push_back({posN, posL-i});
            break;
          }
          else{break;}
        }
    return result;
}
char Rook::getType(){
    return 'R';
}
Piece* Rook::makeCopy(){
    Rook* x=new Rook(this->color, this->posN, this->posL);
    
    return x;
}
int Rook::getValue(){return 5;}
