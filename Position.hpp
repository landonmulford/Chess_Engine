//
//  Position.hpp
//  Chess
//
//  Created by Landon Mulford on 5/12/24.
//

#ifndef Position_hpp
#define Position_hpp
#include "Piece.hpp"
#include <stdio.h>
#include "Pawn.hpp"
#include "Knight.hpp"
#include "Bishop.hpp"
#include "Rook.hpp"
#include "Queen.hpp"
#include "King.hpp"
#include <string>
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <map>
#include <cctype>
using namespace std;

class Position{



public:
    
    const static int depth=6;
    //int currentDepth;
    int blackKing[2], whiteKing[2];
    Piece* board[8][8];
    int material;
    bool castleRights[4];
    int ep[2]={-1, -1};

    
    //Position* parent;
    //Position* bestChild;
    unordered_set<Piece*> whitePieces;
    unordered_set<Piece*> blackPieces;
    //unordered_map<Piece, unordered_map<int[2],Position*>> OrganizedMoves;
    map<double, Position*> sortedPositions;
    unordered_map<Piece*, vector<vector<int>>> unsortedPositions;
   // int move[2];
    
    //int moveNum;
   bool whiteToMove;
    Position(const string& x){
        cout<<"string constructor called";
        int index=0;
        for(int pos_N=0; pos_N<8; pos_N++){
            if(x[index]==' ') break;
            for(int pos_L=0; pos_L<=9; pos_L++){
                if(x[index]==' ') break;
                if(x[index]=='/'){
                    index++;
                    break;
                }
                if(isdigit(x[index])){
                    pos_L+=x[index]-48;
                    index++;
                }
                if (pos_L<8){
                    if(x[index]=='K'){
                        whiteKing[0]=7-pos_N;
                        whiteKing[1]=pos_L;
                    }
                    else if(x[index]=='k'){
                        blackKing[0]=7-pos_N;
                        blackKing[1]=pos_L;
                    }
                    //POSITION HASNT Been consturcted yet so it cant do this
                    Piece* a=generatePiece(x[index], 7-pos_N, pos_L);
                    board[7-pos_N][pos_L]=a;
                    if(a->color) whitePieces.insert(a);
                    else blackPieces.insert(a);
                    index++;
                }
                
            }
        }
        index++;
        if(x[index]=='w') whiteToMove=true;
        else whiteToMove=false;
        index++;
        //insert castle stuff
        while(true){
            if(x[index]=='K') castleRights[0]=true;
            else if(x[index]=='Q') castleRights[1]=true;
            else if(x[index]=='k') castleRights[2]=true;
            else if(x[index]=='q') castleRights[3]=true;
            else break;
        }
        index++;
        if(x[index!='-']){
            ep[1]=(int)x[index]-97;
            index++;
            ep[0]=x[index];
        }
        
        
        
    }
    Position(const Position& old){
        //cout<<"Copy constructor called";
        for (int x=0 ; x <8; x++){
          for (int y=0 ; y <8; y++){
            board[x][y] = old.board[x][y];
              //THIS CALLS COPY ASSIGNMENT SO WILL NOT WORK
          }
        }
        for(int i=0; i<4; i++){
            castleRights[i]=old.castleRights[i];
        }
        /*does this change things
        color=*(new bool(old.color));
        eval=*(new double(old.eval));
        
        //this->blackKing=old->blackKing;
       // this->whiteKing=old->whiteKing;
        whitePieces=*(new unordered_set<Piece*>(old.whitePieces));
        blackPieces=*(new unordered_set<Piece*>(old.blackPieces));
        sortedPositions=*(new map<double, Position*>(old.sortedPositions));
        currentDepth=old.currentDepth+1;
        //this copies the sorted Positions, so maybe get rid of this or clear it at some point
        //do I actually need to do all this for deep copy, or only for the stuff that is dynamic
        */
        whiteToMove=old.whiteToMove;
        //if(old.next==nullptr) next=nullptr;
        //else next=new Position(*(old.next));
        //currentDepth=old.currentDepth;
       
        
        blackKing[0]=old.blackKing[0];
        blackKing[1]=old.blackKing[1];
        whiteKing[0]=old.whiteKing[0];
        whiteKing[1]=old.whiteKing[1];
        //whitePieces=*(new unordered_set<Piece*>(old.whitePieces));
        //blackPieces=*(new unordered_set<Piece*>(old.blackPieces));
        for(Piece* a:old.whitePieces){
            Piece* temp=a;
            whitePieces.insert(temp);
        }
        for(Piece* a:old.blackPieces){
            Piece* temp=a;
            blackPieces.insert(temp);
        }
        
        //NO COPY FOR SORteD POSItionS
        /*for(auto a: sortedPositions){
            double x=a.first;
            Position* y=a.second;
            sortedPositions.insert({x,y});
        }*/
    };
    
   
     
    ~Position(){
        for(int i=0; i<8; i++){
            for(int j=0; j<8; j++){
                delete board[i][j];
                //interesting, when Position is a pointer no error, but this is a pointer regardless so i feel like this needs to be here, because they are reated with new, maybe theres no new when copy happens?
            }
        }
        //delete next;
        //delete &color;
        //delete &eval;
        /*for(Piece* a: whitePieces){
            delete a;
        }
        for(Piece* b: blackPieces){
            delete b;
        }*/
        //delete &whitePieces;
        //perhaps leakage inside white and black Pieces
        //maybe I dont have to do this, or maybe I need to add this to constructor
        //delete &blackPieces;
        for(auto a:sortedPositions){
            delete a.second;
        }
        
    };
    Position& operator=(const Position& old)
    {
        for (int x=0 ; x <8; x++){
          for (int y=0 ; y <8; y++){
            board[x][y] = old.board[x][y];
              //THIS CALLS COPY ASSIGNMENT SO WILL NOT WORK
          }
        }
        for(int i=0; i<4; i++){
            castleRights[i]=old.castleRights[i];
        }
        //does this change things
        /*color=*(new bool(old.color));
        eval=*(new double(old.eval));
        
        //this->blackKing=old->blackKing;
       // this->whiteKing=old->whiteKing;
        whitePieces=*(new unordered_set<Piece*>(old.whitePieces));
        blackPieces=*(new unordered_set<Piece*>(old.blackPieces));
        sortedPositions=*(new map<double, Position*>(old.sortedPositions));
        currentDepth=old.currentDepth+1;
        //this copies the sorted Positions, so maybe get rid of this or clear it at some point
        //do I actually need to do all this for deep copy, or only for the stuff that is dynamic
        */
        whiteToMove=old.whiteToMove;
        //currentDepth=old.currentDepth;
        //next=new Position(*next);
        blackKing[0]=old.blackKing[0];
        blackKing[1]=old.blackKing[1];
        whiteKing[0]=old.whiteKing[0];
        whiteKing[1]=old.whiteKing[1];
        whitePieces=*(new unordered_set<Piece*>(old.whitePieces));
        blackPieces=*(new unordered_set<Piece*>(old.blackPieces));
        /*
        for(Piece* a:old.whitePieces){
            Piece* temp=a;
            whitePieces.insert(temp);
        }
        for(Piece* a:old.blackPieces){
            Piece* temp=a;
            blackPieces.insert(temp);
        }*/
        for(auto a: sortedPositions){
            double x=a.first;
            Position* y=a.second;
            sortedPositions.insert({x,y});
        }
        
        return *this;
    };
    /*Position(Position &&old)                                   // Move ctor
    {
        std::cout<<"Move constructor\n";
        for (int x=0 ; x <8; x++){
          for (int y=0 ; y <8; y++){
            board[x][y] = old.board[x][y];
              //THIS CALLS COPY ASSIGNMENT SO WILL NOT WORK
          }
        }
        //does this change things
        color=*(new bool(old.color));
        eval=*(new double(old.eval));
        
        //this->blackKing=old->blackKing;
       // this->whiteKing=old->whiteKing;
        whitePieces=*(new unordered_set<Piece*>(old.whitePieces));
        blackPieces=*(new unordered_set<Piece*>(old.blackPieces));
        sortedPositions=*(new map<double, Position*>(old.sortedPositions));
        currentDepth=old.currentDepth+1;
        //this copies the sorted Positions, so maybe get rid of this or clear it at some point
        //do I actually need to do all this for deep copy, or only for the stuff that is dynamic
        
        currentDepth=old.currentDepth+1;
        eval=old.eval;
        color=old.color;
        blackKing[0]=old.blackKing[0];
        blackKing[1]=old.blackKing[1];
        whiteKing[0]=old.whiteKing[0];
        whiteKing[1]=old.whiteKing[1];
        for(Piece* a:old.whitePieces){
            Piece* temp=a;
            whitePieces.emplace(temp);
        }
        for(Piece* a:old.blackPieces){
            Piece* temp=a;
            blackPieces.emplace(temp);
        }
        
        
    };*/
    
    
    Position(){
        //currentDepth=0;
        whiteToMove=true;
        
        board[0][0]=new Rook(true,0,0);
        board[0][1]=new Knight(true,0,1);
        board[0][2]=new Bishop(true,0,2);
        board[0][3]=new Queen(true,0,3);
        board[0][4]=new King(true,0,4);
        board[0][5]=new Bishop(true,0,5);
        board[0][6]=new Knight(true,0,6);
        board[0][7]=new Rook(true,0,7);
        board[7][0]=new Rook(false,7,0);
        board[7][1]=new Knight(false,7,1);
        board[7][2]=new Bishop(false,7,2);
        board[7][3]=new Queen(false,7,3);
        board[7][4]=new King(false,7,4);
        board[7][5]=new Bishop(false,7,5);
        board[7][6]=new Knight(false,7,6);
        board[7][7]=new Rook(false,7,7);
        for(int i=0; i<=7; i++){
            board[1][i]= new Pawn(true,1,i);
            board[6][i]= new Pawn(false,6,i);
            //will it still be able to access the pawn generateMoves
            }
        for(int i=0; i<2; i++){
            for(int j=0; j<8; j++){
                whitePieces.insert(board[i][j]);
                blackPieces.insert(board[7-i][j]);
                //CHECK THIS MAKE SURE POINTER SHIT IS GOOD BUT IT SHOULD BE
            }
            
            
        }
    };
    
    
    bool isCheckMate();
    void display();
    bool makeMove(int n1, int l1, int n2, int l2);
    bool go();
    bool isCheck();
    double getEval();
    void generateSortedPositions();
    tuple<double, Position*> recommend(int currentDepth=0);
    //double getAverageOfKidsEval();
    double getMaxEval();
    Position* newPosition(Piece* a,vector<int> x) const;
    bool rand(int rank, int total, bool white);
    Piece* generatePiece(char c, int posN, int posL);
    bool generateUnsortedPositions();
    void whiteCastle();
    void blackCastle();
    void enPassant();

    
    
};


#endif /* Position_hpp */
