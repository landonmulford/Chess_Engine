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

int main(int argc, const char * argv[]) {
    
    
    bool play=true;
    while(play){
        cout<<"Insert FEN"<<endl;
        string fen;
        getline(cin, fen);
        Position* game=new Position(fen);
        Position* after=get<1>(game->recommend());
        after->display();
    }

    return 0;
};

