#ifndef PLAYER_H
#define PLAYER_H

//============================================//
// Header Files                               //
//============================================//

#include <iostream>

//============================================//
// Namespaces                                 //
//============================================//

using namespace std; 

//============================================//
// Player class                               //
//============================================//

class Player {

    private: 
        string first, full;
        int wins, losses, draws, playerNumber;
        char piece;
    public:
        void addStat(int);
        void setPlayerNumber(int);  
        void setFirstName(string, int); 
        void setFullName(string);
        void setPiece(char); 
        char getPiece();
        int getPlayerNumber();  
        int getWins(); 
        int getLosses(); 
        int getDraws();
        string getFullName();
        string getFirstName();
        Player(); 
};

#endif
