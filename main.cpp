//
//  main.cpp
//  Chess
//
//  Created by Landon Mulford on 5/12/24.
//
#include <string>
#include <iostream>
#include "Position.hpp"
#include "Piece.hpp"
#include "Pawn.hpp"
#include "Knight.hpp"
#include "Bishop.hpp"
#include "Rook.hpp"
#include "Queen.hpp"
#include "King.hpp"
//maybe do piece instead of Piece*, could improve big O
//Potential issues: white to move black to move, loading and outputting board, giving good recs, hella things

int main(int argc, const char * argv[]) {
    
    
    bool play=true;
    while(play){
        cout<<"Insert FEN"<<endl;
        string fen;
        getline(cin, fen);
        Position* game=new Position(fen);
        Position* after=get<1>(game->recommend());
        //game->recommend();
        //Position* current=after;
        /*while(current){
            current->display();
            current=current->next;
        }*/
        after->display();
    }
    //cout<<game->blackKing[0]<<" "<<game->blackKing[1];
    //cout<<game->isCheck()<<game->isCheckMate();
   
   
    //game->display();
    //newPos works?, could be doing it repetively or theres an issue in the pawn shit
    //Position* newPos=game->newPosition(game->board[1][0], {3,0});
   // newPos->display();
    //game->board[1][1]->generateMoves(game->board, true);
    //recommend is returning null positions
    
    //Position* after=get<1>(game->recommend());
    
    //after->display();
    /*Position* current=game;
    while(current){
        current->display();
        current=current->next;
    }
  //Position* after=get<1>(get<1>((get<1>(game->recommend()))->recommend())->recommend());
   //after->display();
   // for(auto a:game->sortedPositions){
   //     a.second->display();
  //  }
   
  //  if(afterMove==nullptr){
  //      cout<<"Fuck";
 //  }
    //copy constructor*/
    return 0;
};


//Position* loadPosition(string a){};
