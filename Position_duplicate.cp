//
//  Position.cpp
//  Chess
//
//  Created by Landon Mulford on 5/12/24.
//

//Overall question, do I need the currentPosition pointer or can i just do this pointer??
#include "Position.hpp"
#include <iostream>
//void Position::display(){}
//bool Position::makeMove(<#int n1#>, <#int l1#>, <#int n2#>, <#int l2#>){}
//bool Position::go(){}
//bool Position::isCheck(){}
//void Position::setEval(){}
//what if newPosition was a Piece function, i think this might work
 Position* Position::newPosition(Piece* a, vector<int> x) const{
    /* cout<<"Before  ";
    Position newPosition=*this;
     cout<<"After  ";
     cout<<"EvalX= "<<newPosition.evalX;
    //this should call copy
    Position* pointer=&newPosition;
     cout<<"EvalX of Pointer = "<<pointer->evalX;*/
     Position* pointer=new Position(*this);
     //*pointer=*this;
     //If new is needed, then needs hella if statements
     //or
   /*  if(a->getType()=='P') {
         pointer->board[x[0]][x[1]]=new Pawn(*a);
     else if(a->getType()=='N') Knight* copy=new Knight(*a);
     else if (a->getType()=='B') Bishop* copy=new Bishop(*a);
     else if (a->getType()=='R') Rook* copy=new Rook(*a);
     else if (a->getType()=='Q') Queen* copy=new Queen(*a);
     else if (a->getType()=='K') King* copy=new King(*a);
     
     auto penis=copy;*/
     
     Piece* copy=a->makeCopy();
     
     //can it convert to a Pawn
    
//     
    //copy doesnt work for some reason
     //i changed this from ! to no !
     if(pointer->whiteToMove){
         if(a->getType()=='K') {
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
     
    pointer->board[a->posN][a->posL]=nullptr;
    pointer->board[x[0]][x[1]]=copy;
    copy->posN=x[0];
    copy->posL=x[1];
    pointer->whiteToMove=!pointer->whiteToMove;
    
    //pointer->display();
     
    //pointer->display();
    return pointer;
    //worry about how to change board in copy without changing og, maybe could use <array>
    //SOMEWHERE, WHITEPIECES AND BLACK PIECES GETS FUCKED
}
bool Position::generateUnsortedPositions(){
    if(this->whiteToMove){
        for(Piece* a:this->whitePieces){
            //cout<<a->getType()<<endl;
            for(vector<int> t:a->generateMoves(this->board, true)){
                
                if(t[0]==blackKing[0]&&t[1]==blackKing[1]) return false;
                else{
                    unsortedPositions[a].push_back(t);
                }
            }
        }
    }
    if(!this->whiteToMove){
        for(Piece* a:this->blackPieces){
            
            for(vector<int> t:a->generateMoves(this->board, true)){
                
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
    for(auto a:unsortedPositions){
        for(vector<int> t:a.second){
            Position* newPos=newPosition(a.first, t);
            sortedPositions[newPos->getEval()]=newPos;
        }
    }
}
//potetnial issues, maybe the currentDepth part
tuple<double, Position*> Position::recommend(int currentDepth){
    
    //this->display();
    if(currentDepth>=depth) {
        /*Position* t=new Position(*this);
        t->next=nullptr;
        return {t->getEval(), t};*/
        return {this->getEval(), this};
    }
    generateSortedPositions();
    //generateMoves is done in eval
    //cout<<lengthOfSorted;

    //cout<<lengthOfSorted;
    tuple<double, Position*> maxTuple;
    if(whiteToMove) maxTuple={INT_MIN, nullptr};
    else maxTuple={INT_MAX, nullptr};
    
    
    //this is wrong but hopefully doesn't really matter
    Position* bestA;
    
    //double average=getAverageOfKidsEval();
    int iterator=0;
    //bool legal=true;
    //while(legal){
        for(auto a:sortedPositions){
            
            
            if(a.second->generateUnsortedPositions()){
                //iterates through legal moves, sorted by eval after 1 move
                //maybe do rand based on depth and just have it pick random moves
                if(rand(iterator, sortedPositions.size(), whiteToMove)){
                    //a.second->display();
                    //selects some moves to explore, favoring those with high evals after first move
                    //get<1>(a)->whiteToMove=!get<1>(a)->whiteToMove;
                    //cout<<"Position above is check: "<<a.second->isCheck()<<"Position above is checkmate: "<<a.second->isCheckMate()<<" "<<a.first;
                    //if(whiteToMove&&a.first>=1000) return a;
                    //if(!whiteToMove&&a.first<=-1000) return a;
                    //a.second->whiteToMove=!a.second->whiteToMove;
                    tuple<double, Position*> currentTuple=get<1>(a)->recommend(currentDepth+1);
                    //recursively calls rrecommend and saves "true eval" and position of each candidate move
                    if(this->whiteToMove&&get<0>(currentTuple)>get<0>(maxTuple)){
                        maxTuple=currentTuple;
                        bestA=a.second;
                    }
                    //makes sure white saves higest eval
                    else if(!(this->whiteToMove)&&get<0>(currentTuple)<get<0>(maxTuple)){
                        //get<1>(currentTuple)->display();
                        //    cout<<"above is new candidate, previous max was "<<get<0>(maxTuple)<<" new max is "<<get<0>(currentTuple);
                        
                        maxTuple=currentTuple;
                        bestA=a.second;
                    }
                    //makes sure black saves lowest eval
                    
                }
                iterator++;
            }
            //updates iterator for the random function
        }
    /*if(bestA==nullptr){
        if(isCheck()){
            if
        }
    }*/
        
        //get<1>(maxTuple)->display();
        //cout<<endl<<"End of recommend called at depth "<<currentDepth<<endl;
        
        /*Position* x=new Position(*bestA);
         Position* y=new Position(*get<1>(maxTuple));
         x->next=y;*/
        
        //this->next=x->next;
        //get<1>(maxTuple)->display();
        //Position* current=new Position(*this);
        //next=new Position(*get<1>(maxTuple));
        //current->next=next;
        //maybe maxTuple needs to be edited
        /* if(currentDepth==0){
         Position* a=x;
         while(a){
         a->display();
         a=a->next;
         }
         }*/
        /*bestA->whiteToMove=!bestA->whiteToMove;
        if(bestA->isCheck()){
            sortedPositions.erase(get<0>(maxTuple));
            bestA=nullptr;
            if(whiteToMove) maxTuple={INT_MIN, nullptr};
            else maxTuple={INT_MAX, nullptr};
            iterator=0;
        }
        else{
            legal=false;
            bestA->whiteToMove=!bestA->whiteToMove;
        
        }*/
        
    //}
    
    return {get<0>(maxTuple), bestA};
    //return maxTuple;
    //returns maxTuple which allows recursion to work
    
    //best child=getBestChild dont think I need this
    //somehow keep track of best move dont think i need this
    //is changing eval here going to change it in other places think this is good
    //ADD MEMOIZATION ALSO WHITE VS BLACK and make sure currentDepth has no issues
}
//double Position::getAverageOfKidsEval(){}
bool Position::rand(int rank, int total, bool color){
    if(rank<5)return true;
    double prob;
    if(!color)prob=sqrt((total-rank)/total);
    else prob=sqrt((rank+1)/total);
    double output=std::rand()%100+prob*100;
    return output>=100;
    //issues when total is really small
}
double Position::getEval(){
    double eval=0;
    if(isCheck()){
        
        if(whiteToMove){
            eval-=2;
            
            if(isCheckMate()) return INT_MIN+1;
        }
        else{
            eval+=2;
            if(isCheckMate()) return INT_MAX-1;
        }
    }
    eval+=material;
    
    //could increase efficiency on this
    
    double whitePosition=0;
    double blackPosition=0;
    //can do space thing
    
    for(Piece* a: whitePieces){
        whitePosition+=a->posN/4;
        whitePosition-=(abs(3.5-a->posL))/10;
    }
    for(Piece* a: blackPieces){
        blackPosition+=(7-a->posN)/4;
        blackPosition-=(abs(3.5-a->posL))/10;
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
    //think about who's move it is
    Position* x=new Position(*this);
    x->whiteToMove=!x->whiteToMove;
    
    if(x->whiteToMove){
        for(Piece* a:x->whitePieces){
            //cout<<a->getType()<<endl;
            for(vector<int> t:a->generateMoves(x->board, true)){
                
                if(t[0]==blackKing[0]&&t[1]==blackKing[1]) return true;
            }
        }
    }
    if(!x->whiteToMove){
        for(Piece* a:x->blackPieces){
            for(vector<int> a:a->generateMoves(x->board, true)){
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

bool Position:: isCheckMate(){
    //display();
    if(!isCheck()) return false;
    if(whiteToMove){
        for(Piece* a:whitePieces){
            //iterates through each piece for white
            //each piece will store a 2 item array, then we can just make new positition in with newPosition
            for(auto x:a->generateMoves(this->board, true)){
                
                //Piece getting passed in is not accurate, means something is wrong with
                Position* newPos=newPosition(a, x);
                newPos->whiteToMove=!newPos->whiteToMove;
                if(newPos->isCheck()==false) return false;
                //instead of legalMoves, do generateMoves
                
                //iterates through each legal move for each piece and adds them to sorted map*/
            }
        }
        
    }
            
    else{
        for(Piece* a:blackPieces){
            //iteratess through each piece for black
            for(auto x:a->generateMoves(this->board, true)){
                Position* newPos=newPosition(a, x);
                newPos->whiteToMove=!newPos->whiteToMove;
                if(newPos->isCheck()==false){
                    return false;
                }
                //iterates through each legal move for each piece and adds them to sorted map
            }
        }
    }
    return true;
    
}



/*
 #include "Position.hpp"
 void Position::display(){}
 bool Position::makeMove(<#int n1#>, <#int l1#>, <#int n2#>, <#int l2#>){}
 bool Position::go(){}
 bool Position::isCheck(){}
 void Position::setEval(){}
 Position* Position::newPosition(Piece a, int x[]){}
 int Position::generateMoves(Position* currentPosition){
     int count=0;
     if(currentPosition->color){
         for(Piece a:whitePieces){
             //iterates through each piece for white
             for(Position* x:a.legalMoves){
                 double eval=x->eval;
                 sortedPositions[eval]=x;
                 count++;
             }
         }
     }
     else{
         for(Piece a:blackPieces){
             //iteratess through each piece
             for(Position* x:a.legalMoves){
                 double eval=x->eval;
                 sortedPositions[eval]=x;
                 count++;
             }
         }
     }
     return count;
 }
 tuple<double, Position*> Position::recommend(Position* currentPosition, int currentDepth=0){
     if(currentDepth==depth) return {currentPosition->eval, currentPosition};
     tuple<double, Position*> maxTuple;
     int lengthOfSorted=generateMoves(currentPosition);
     double average=getAverageOfKidsEval();
     int iterator=0;
     for(auto a:sortedPositions){
         //iterates through legal moves, sorted by eval after 1 move
         if(rand(iterator, lengthOfSorted, currentPosition->color)||isCheck()){
             //selects some moves to explore, favoring those with high evals after first move
             tuple<double, Position*> currentTuple=recommend(a.second, currentDepth+1);
             //recursively calls recommend and saves "true eval" and position of each candidate move
             if(currentPosition->color&&get<0>(currentTuple)>get<0>(maxTuple)){
                 maxTuple=currentTuple;
             }
             //makes sure white saves higest eval
             else if(!(currentPosition->color)&&get<0>(currentTuple)<get<0>(maxTuple)){
                 maxTuple=currentTuple;
             }
             //makes sure black saves lowest eval
             
         }
         iterator++;
         //updates iterator for the random function
         }
     return maxTuple;
     //returns maxTuple which allows recursion to work
     
     //best child=getBestChild dont think I need this
     //somehow keep track of best move dont think i need this
     //is changing eval here going to change it in other places think this is good
     //ADD MEMOIZATION ALSO WHITE VS BLACK
 }
 double Position::getAverageOfKidsEval(){}
 bool Position::rand(int rank, int total, bool color){
     double prob;
     if(color)prob=sqrt((total-rank)/total);
     else prob=sqrt((rank+1)/total);
     double output=std::rand()%100+prob*100;
     return output>=100;
     //issues when total is really small
 }
 
*/
