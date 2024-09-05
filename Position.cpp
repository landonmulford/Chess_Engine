//
//  Position.cpp
//  Chess
//
//  Created by Landon Mulford on 5/12/24.
//
#include "Position.hpp"
#include <iostream>
 Position* Position::newPosition(Piece* a, vector<int> x) const{
     Position* pointer=new Position(*this);
     Piece* copy=a->makeCopy();
     copy->posN=x[0];
     copy->posL=x[1];
    
     if(a->getType()=='P'){
         //details with en passant
         if(whiteToMove&&x[0]==ep[0]&&x[1]==ep[1]){
             pointer->board[ep[0]][ep[1]]=pointer->board[ep[0]-1][ep[1]];
             pointer->board[ep[0]-1][ep[1]]=nullptr;
         }
         else if(!whiteToMove&&x[0]==ep[0]&&x[1]==ep[1]){
             pointer->board[ep[0]][ep[1]]=pointer->board[ep[0]+1][ep[1]];
             pointer->board[ep[0]+1][ep[1]]=nullptr;
         }
         else if(x[0]>=7){
            //details with promotion
             if(x[0]==7){
                 copy=new Queen(true, 7, x[1]);
             }
             else if(x[0]==8){
                 copy=new Rook(true, 7, x[1]);
             }
             else if(x[0]==9){
                 copy=new Knight(true, 7, x[1]);
             }
             else if(x[0]==10){
                 copy=new Bishop(true, 7, x[1]);
             }
             pointer->material+=copy->getValue()-1;
             x[0]=7;
         }
         else if(x[0]<=0){
             if(x[0]==0){
                 copy=new Queen(false, 0, x[1]);
             }
             else if(x[0]==-1){
                 copy=new Rook(false, 0, x[1]);
             }
             else if(x[0]==-2){
                 copy=new Knight(false, 0, x[1]);
             }
             else if(x[0]==-3){
                 copy=new Bishop(false, 0, x[1]);
             }
             pointer->material-=copy->getValue()+1;
             x[0]=0;
         }
         
     }
     if(pointer->whiteToMove){
       //details with castling
         if(a->getType()=='K') {
             if(x[0]==-1){
                 if(x[1]==6){
                     Piece* rookCopy=new Rook(true, 0, 5);
                     pointer->whitePieces.erase(pointer->board[0][7]);
                     pointer->board[0][7]=nullptr;
                     pointer->whitePieces.insert(rookCopy);
                 }
                 if(x[1]==2){
                     Piece* rookCopy=new Rook(true, 0, 3);
                     pointer->whitePieces.erase(pointer->board[0][0]);
                     pointer->board[0][0]=nullptr;
                     pointer->whitePieces.insert(rookCopy);
                 }
                 x[0]=0;
             }
             pointer->whiteKing[0]=x[0];
             pointer->whiteKing[1]=x[1];
         }
         pointer->whitePieces.erase(a);
         pointer->whitePieces.insert(copy);
         if(pointer->board[x[0]][x[1]]!=nullptr){
             pointer->blackPieces.erase(pointer->board[x[0]][x[1]]);
             pointer->material+=board[x[0]][x[1]]->getValue();
         }
         
     }
     else{
         if(a->getType()=='K') {
             if(x[0]==8){
                 if(x[1]==6){
                     Piece* rookCopy=new Rook(true, 7, 5);
                     pointer->whitePieces.erase(pointer->board[7][7]);
                     pointer->board[7][7]=nullptr;
                     pointer->whitePieces.insert(rookCopy);
                 }
                 if(x[1]==2){
                     Piece* rookCopy=new Rook(true, 7, 3);
                     pointer->whitePieces.erase(pointer->board[7][0]);
                     pointer->board[7][0]=nullptr;
                     pointer->whitePieces.insert(rookCopy);
                 }
                 x[0]=7;
             }
             pointer->blackKing[0]=x[0];
             pointer->blackKing[1]=x[1];
         }
         pointer->blackPieces.erase(a);
         pointer->blackPieces.insert(copy);
         if(pointer->board[x[0]][x[1]]!=nullptr){
             pointer->whitePieces.erase(pointer->board[x[0]][x[1]]);
             pointer->material-=board[x[0]][x[1]]->getValue();
         }
     }
    //general code for moves
    pointer->board[a->posN][a->posL]=nullptr;
    pointer->board[x[0]][x[1]]=copy;
    pointer->whiteToMove=!pointer->whiteToMove;
    
    return pointer;
}
bool Position::generateUnsortedPositions(){
    enPassant();
    if(this->whiteToMove){
        whiteCastle();
        for(Piece* a:this->whitePieces){
            for(vector<int> t:a->generateMoves(this->board)){
                
                if(t[0]==blackKing[0]&&t[1]==blackKing[1]) return false;
                else{
                    unsortedPositions[a].push_back(t);
                }
            }
        }
    }
    else if(!this->whiteToMove){
        blackCastle();
        for(Piece* a:this->blackPieces){
            
            for(vector<int> t:a->generateMoves(this->board)){
                
                if(t[0]==whiteKing[0]&&t[1]==whiteKing[1]) return false;
                else{
                    unsortedPositions[a].push_back(t);
                }
            }
        }
    }
    return true;
}
void Position::generateSortedPositions(){
    if(unsortedPositions.size()==0) generateUnsortedPositions();
    if(sortedPositions.size()>0) sortedPositions.clear();
    for(auto a:unsortedPositions){
        for(vector<int> t:a.second){
            Position* newPos=newPosition(a.first, t);
            sortedPositions[newPos->getEval()]=newPos;
        }
    }

}
void Position::enPassant(){
    
    if(ep[0]==2){
        if(board[ep[0]+1][ep[1]+1]&&board[ep[0]+1][ep[1]+1]->getType()=='P'&&board[ep[0]+1][ep[1]+1]->color==whiteToMove){
            unsortedPositions[board[ep[0]+1][ep[1]+1]].push_back({ep[0], ep[1]});
        }
        if(board[ep[0]+1][ep[1]-1]&&board[ep[0]+1][ep[1]-1]->getType()=='P'&&board[ep[0]+1][ep[1]-1]->color==whiteToMove){
            unsortedPositions[board[ep[0]+1][ep[1]-1]].push_back({ep[0], ep[1]});
        }
    }
    if(ep[0]==5){
        if(board[ep[0]-1][ep[1]+1]&&board[ep[0]-1][ep[1]+1]->getType()=='P'&&board[ep[0]-1][ep[1]+1]->color==whiteToMove){
            unsortedPositions[board[ep[0]-1][ep[1]+1]].push_back({ep[0], ep[1]});
        }
        if(board[ep[0]-1][ep[1]-1]&&board[ep[0]-1][ep[1]-1]->getType()=='P'&&board[ep[0]-1][ep[1]-1]->color==whiteToMove){
            unsortedPositions[board[ep[0]][ep[1]-1]].push_back({ep[0], ep[1]});
        }
    }
}
tuple<double, Position*> Position::recommend(int currentDepth){
    
    //bottom of depth tree, with slight changes to make it more tailored to endgames
    if(currentDepth>=depth||(whitePieces.size()+blackPieces.size()<6&&currentDepth>=depth-2)) {
        return {this->getEval(), this};
    }
    generateSortedPositions();
    tuple<double, Position*> maxTuple;
    if(whiteToMove) maxTuple={INT_MIN, nullptr};
    else maxTuple={INT_MAX, nullptr};
    Position* bestA=nullptr;
    int iterator=0;
    
        for(auto a:sortedPositions){
            
            if(a.second->generateUnsortedPositions()){
                
                if(rand(iterator, sortedPositions.size(), whiteToMove)){

                 //recursively calls recommend and saves "true eval" and position of each candidate move
                    tuple<double, Position*> currentTuple=get<1>(a)->recommend(currentDepth+1);
                   //makes sure white saves higest eval  
                    if(this->whiteToMove&&get<0>(currentTuple)>get<0>(maxTuple)){
                        maxTuple=currentTuple;
                        bestA=a.second;
                    }
                   //makes sure black saves lowest eval
                    else if(!(this->whiteToMove)&&get<0>(currentTuple)<get<0>(maxTuple)){
                      
                        maxTuple=currentTuple;
                        bestA=a.second;
                    }
                   
                }
                iterator++;
            }
            //updates iterator for the random function
        }
    if(!bestA){
        if(isCheck()){
            if(whiteToMove) return{INT_MIN+currentDepth, this};
            else return{INT_MAX-currentDepth, this};
        }
        else return{0, this};
    }
    
    return {get<0>(maxTuple), bestA};
}

bool Position::rand(int rank, int total, bool color){
    if(rank<5)return true;
    double size=35-(whitePieces.size()+blackPieces.size());
    double prob;
    if(!color)prob=sqrt((total-rank)/total);
    else prob=sqrt((rank+1)/total);
    double output=std::rand()%100+prob*100;
    return output>=100;
}
double Position::getEval(){
    double eval=0;
    eval+=material;
    
    double whitePosition=0;
    double blackPosition=0;
 
    for(Piece* a: whitePieces){
        whitePosition+=a->posN/4;
        whitePosition-=(abs(3.5-a->posL))/15;
    }
    for(Piece* a: blackPieces){
        blackPosition+=(7-a->posN)/4;
        blackPosition-=(abs(3.5-a->posL))/15;
    }
    eval+=(whitePosition/(whitePieces.size()+1)-blackPosition/(blackPieces.size()+1));
    
    eval+=(std::rand()%1000)/100000.1;
    
    return eval;
}
void Position::display(){
    cout<<endl;
    for(int i=7; i>=0; i--){
        for(int j=0; j<8; j++){
            if(board[i][j]!=nullptr){
                if(board[i][j]->color) cout<<board[i][j]->getType()<<" ";
                else cout<<char(board[i][j]->getType()+('a'-'A'))<<" ";
            }
            else cout<<"  ";
        }
        cout<<endl;
    }
    for(int i=0; i<8; i++) cout<<"--";
    cout<<endl;
}
bool Position::isCheck(){
    Position* x=new Position(*this);
    x->whiteToMove=!x->whiteToMove;
    
    if(x->whiteToMove){
        for(Piece* a:x->whitePieces){
            for(vector<int> t:a->generateMoves(x->board)){
                
                if(t[0]==blackKing[0]&&t[1]==blackKing[1]) return true;
            }
        }
    }
    if(!x->whiteToMove){
        for(Piece* a:x->blackPieces){
            for(vector<int> a:a->generateMoves(x->board)){
                if(a[0]==whiteKing[0]&&a[1]==blackKing[1]) return true;
            }
        }
    }
    return false;
}
    
Piece* Position::generatePiece(char c, int posN, int posL){
    Piece* a;
         if(c=='p') a=new Pawn(false, posN, posL);
    else if(c=='P') a=new Pawn(true, posN, posL);
    else if(c=='n') a=new Knight(false, posN, posL);
    else if(c=='N') a=new Knight(true, posN, posL);
    else if(c=='b') a=new Bishop(false, posN, posL);
    else if(c=='B') a=new Bishop(true, posN, posL);
    else if(c=='r') a=new Rook(false, posN, posL);
    else if(c=='R') a=new Rook(true, posN, posL);
    else if(c=='q') a=new Queen(false, posN, posL);
    else if(c=='Q') a=new Queen(true, posN, posL);
    else if(c=='k') a=new King(false, posN, posL);
    else if(c=='K') a=new King(true, posN, posL);
    return a;
}
void Position::whiteCastle(){
    if(isCheck()) return;
    if(castleRights[0]){
        if(!board[0][5]&&!board[0][6]){
            for(int i=5; i<8; i++){
                if(i==7) unsortedPositions[board[0][4]].push_back({-1, 6});
                Position* testPosition=newPosition(board[0][4], {0,i});
                testPosition->whiteToMove=!testPosition->whiteToMove;
                if(testPosition->isCheck()) break;
            }
        }
    }
    if(castleRights[1]){
        if(!board[0][3]&&!board[0][2]){
            for(int i=2; i<5; i++){
                if(i==4) unsortedPositions[board[0][4]].push_back({-1, 2});
                Position* testPosition=newPosition(board[0][4], {0,i});
                testPosition->whiteToMove=!testPosition->whiteToMove;
                if(testPosition->isCheck()) break;
            }
        }
    }
}
void Position::blackCastle(){
    if(castleRights[2]){
        if(!board[7][5]&&!board[7][6]){
            for(int i=5; i<8; i++){
                if(i==7) unsortedPositions[board[7][4]].push_back({8, 6});
                Position* testPosition=newPosition(board[7][4], {7,i});
                testPosition->whiteToMove=!testPosition->whiteToMove;
                if(testPosition->isCheck()) break;
            }
        }
    }
    if(castleRights[3]){
        if(!board[7][3]&&!board[7][2]){
            for(int i=2; i<5; i++){
                if(i==4) unsortedPositions[board[7][4]].push_back({8, 2});
                Position* testPosition=newPosition(board[7][4], {7,i});
                testPosition->whiteToMove=!testPosition->whiteToMove;
                if(testPosition->isCheck()) break;
            }
        }
    }
}

bool Position:: isCheckMate(){
    //display();
    if(!isCheck()) return false;
    if(whiteToMove){
     //iterates through each piece for white
     //each piece will store a 2 item array, then we can just make new positition in with newPosition
        for(Piece* a:whitePieces){
            
            for(auto x:a->generateMoves(this->board)){
  
                Position* newPos=newPosition(a, x);
                newPos->whiteToMove=!newPos->whiteToMove;
                if(newPos->isCheck()==false) return false;
            }
        }
        
    }
            
    else{
        for(Piece* a:blackPieces){
            //iteratess through each piece for black
            for(auto x:a->generateMoves(this->board)){
                Position* newPos=newPosition(a, x);
                newPos->whiteToMove=!newPos->whiteToMove;
                if(newPos->isCheck()==false){
                    return false;
                }
            }
        }
    }
    return true;
    
}
