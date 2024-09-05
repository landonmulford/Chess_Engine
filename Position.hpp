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
    int blackKing[2], whiteKing[2];
    Piece* board[8][8];
    int material;
    bool castleRights[4];
    int ep[2]={-1, -1};

    unordered_set<Piece*> whitePieces;
    unordered_set<Piece*> blackPieces;

    map<double, Position*> sortedPositions;
    unordered_map<Piece*, vector<vector<int>>> unsortedPositions;
   bool whiteToMove;
//default constructor
     Position(){
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
            }
        for(int i=0; i<2; i++){
            for(int j=0; j<8; j++){
                whitePieces.insert(board[i][j]);
                blackPieces.insert(board[7-i][j]);
            }
            
            
        }
    };
//constructor from input
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
//copy constructor
    Position(const Position& old){
        for (int x=0 ; x <8; x++){
          for (int y=0 ; y <8; y++){
            board[x][y] = old.board[x][y];
          }
        }
        for(int i=0; i<4; i++){
            castleRights[i]=old.castleRights[i];
        }
        
        whiteToMove=old.whiteToMove;
      
       
        
        blackKing[0]=old.blackKing[0];
        blackKing[1]=old.blackKing[1];
        whiteKing[0]=old.whiteKing[0];
        whiteKing[1]=old.whiteKing[1];

        for(Piece* a:old.whitePieces){
            Piece* temp=a;
            whitePieces.insert(temp);
        }
        for(Piece* a:old.blackPieces){
            Piece* temp=a;
            blackPieces.insert(temp);
        }
        
    };
    
   
     //destructor
    ~Position(){
        for(int i=0; i<8; i++){
            for(int j=0; j<8; j++){
                delete board[i][j];
                
            }
        }
       
        for(auto a:sortedPositions){
            delete a.second;
        }
        
    };
//copy assignment operator
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
        whiteToMove=old.whiteToMove;
        blackKing[0]=old.blackKing[0];
        blackKing[1]=old.blackKing[1];
        whiteKing[0]=old.whiteKing[0];
        whiteKing[1]=old.whiteKing[1];
        whitePieces=*(new unordered_set<Piece*>(old.whitePieces));
        blackPieces=*(new unordered_set<Piece*>(old.blackPieces));
        for(auto a: sortedPositions){
            double x=a.first;
            Position* y=a.second;
            sortedPositions.insert({x,y});
        }
        
        return *this;
    };
    
    
   
    
    
    bool isCheckMate();
    void display();
    bool makeMove(int n1, int l1, int n2, int l2);
    bool go();
    bool isCheck();
    double getEval();
    void generateSortedPositions();
    tuple<double, Position*> recommend(int currentDepth=0);
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
