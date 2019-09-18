//============================================//
// Header Files                               //
//============================================//

#include "player.h"

//============================================//
// Adds win/loss/draw based on int parameter  //
//============================================//

void Player::addStat(int statistic)  
{

    switch(statistic)
    {
        case 1: 
            wins += 1; 
            break; 
        case 0: 
            draws += 1; 
            break; 
        default: 
            losses += 1; 
            break; 
    }
    
}

//============================================//
// Set a player's number                      //
//============================================//

void Player::setPlayerNumber(int number) 
{
    playerNumber = number; 
}

//============================================//
// Set player first name                      //
//============================================//

void Player::setFirstName(string f, int x)  
{

    int offset = x;
    while ( f[offset] != ' ' ) 
    {
        offset += 1; 
    }

    int totalChars = offset - x; 
    char firstName[totalChars+1];
    for ( int i = 0; i < totalChars; i++ )
    {
        firstName[i] = f[x+i];
    } 
    firstName[totalChars] = '\0'; 
    first = firstName; 
}

//============================================//
// Set player's full name                     //
//============================================//

void Player::setFullName(string fullName)  
{
    full = fullName; 
}

//============================================//
// Set player's game piece                    //
//============================================//

void Player::setPiece(char p) 
{
    piece = p; 
}

//============================================//
// Returns player's game piece                //
//============================================//

char Player::getPiece() 
{
    return piece;
}

//============================================//
// Returns player's number                    //
//============================================//

int Player::getPlayerNumber() 
{
    return playerNumber; 
}

//============================================//
// Returns number of wins                     //
//============================================//

int Player::getWins() 
{
    return wins; 
}

//============================================//
// Returns number of losses                   //
//============================================//

int Player::getLosses() 
{
    return losses; 
}

//============================================//
// Returns number of draws                    //
//============================================//

int Player::getDraws()
{
    return draws;
}

//============================================//
// Returns player's full name                 //
//============================================//

string Player::getFullName()
{
    return full;
}

//============================================//
// Returns player's first name                //
//============================================//

string Player::getFirstName()
{
    return first;
}

//============================================//
// Player constructor                         //
//============================================//

Player::Player()
{
    wins = 0; 
    draws = 0; 
    losses = 0; 
}
