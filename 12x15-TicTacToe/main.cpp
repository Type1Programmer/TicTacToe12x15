//===========================//
// Tiwong Nance Jr.          //
// 12x15 Tic-Tac-Toe         //
//===========================//

//===========================//
// Header Files              //
//===========================//

#include "player.h" 
#include <iostream> 

//===========================//
// Namespaces                //
//===========================//

using namespace std; 

//===========================//
// Symbolic Constants        //
//===========================//

const string PIECES = "abcde";
const string rows = "ABCDEFGHIJKL"; 
const char MIN_PLAYERS = '2';  
const char MAX_PLAYERS = '5'; 
const int NUM_NAMES = 2; 
const int MIN_ROWS = 3; 
const int MIN_COLUMNS = 3; 
const int MAX_ROWS = 12; 
const int MAX_COLUMNS = 15;
const int MAX_GAMES = 1000;  

//===========================//
// Function Prototypes       //
//===========================//

int getNumPlayers(); 
Player askPlayerName(Player, int); 
int getDimensions(int&, int&); 
int makeMove(Player&, int&, int&, int&, char*); 
int determineTurn(int&, char&, int&, int&, char&, int&); 
string displayError(int); 
void toUpper(char&); 
void toLower(char&); 
void printBoard(char*, int&, int&);  
char* clearBoard(char*, int&); 
int longestNameLength(Player[], int); 
void printGameStats(Player*, int, int, int, int); 
void addWinLossDraw(Player*, int, int, int); 
char* detectWin(char*, int&, int&, bool&); 
bool endGame(); 
int pow(int, int);
int intLen(int); 
int len(string);
istream& getLine(istream&, string&); 

int main() 
{

    string space_over; 
    char lastWinner, lastMove; 
    int gameNumber = 0;
    int totalMoves = 0; 
    int turn = 0;
    bool gameOver = false; 
    bool quitting = false; 
    bool win = false; 
    int l = 0; 
    int num_players, N, M, NxM, move, longest; 
    char* board; 
    num_players = getNumPlayers(); 
    Player players[num_players]; 

    for ( int i = 0; i < num_players; i++ ) 
    {
        players[i] = askPlayerName(players[i], i+1); 
        players[i].setPiece(PIECES[i]);

        if ( len(players[i].getFullName()) > l )
        {
            l = len(players[i].getFullName()); 
        }
    }

    while ( !quitting ) 
    { 
        NxM = getDimensions(N, M); 
        board = clearBoard(board, NxM); 
        gameNumber += 1; 
        cout << "\nGame " << gameNumber << ": Fight!\n";
        printBoard(board, N, M); 

        while ( !gameOver )
        {
            turn = determineTurn(gameNumber, lastWinner, totalMoves, num_players, lastMove, turn); 
            move = makeMove(players[turn], N, M, NxM, board); 
            totalMoves += 1; 
            board[move] = players[turn].getPiece(); 
            board = detectWin(board, M, NxM, win); 

            if ( win ) 
            {
                addWinLossDraw(players, num_players, turn, 0); 
                gameOver = true; 
                win = !win; 
                printBoard(board, N, M); 
                lastWinner = players[turn].getPiece(); 
            }
            else if ( totalMoves == NxM ) 
            {
                addWinLossDraw(players, num_players, turn, 1); 
                gameOver = true; 
                printBoard(board, N, M); 
            }
            else 
            {
                printBoard(board, N, M); 
            }  
            lastMove = players[turn].getPiece(); 
        }
        longest = longestNameLength(players, num_players);  
        printGameStats(players, num_players, l, gameNumber, longest); 
        quitting = endGame();

        if ( gameNumber == MAX_GAMES ) 
        {
            cout << "\nMaximum number of games ( 1000 ) reached.\n"; 
            quitting = true; 
        }
        if ( !quitting )
        {
            gameOver = false; 
            lastMove = ' '; 
            totalMoves = 0; 
        }
    }
    cout << "\nThanks for playing!\n\n"; 
    delete board; 
    board = nullptr; 
} 


//============================================//
// Returns the number of players              //
//============================================//

int getNumPlayers()
{

    bool isValid = false; 
    string num; 
    cout << "\nWelcome to Tic Tac Toe: The Ultimate Edition\n\n"; 

    while ( !isValid ) 
    {
        cout << "Enter the number of players: "; 
        cin >> num; 
        cin.ignore(); 

        if ( len(num) > 1 )
        {
            cout << displayError(5); 
        }
        else if( num[0] >= MIN_PLAYERS  && num[0] <= MAX_PLAYERS )
        {
            isValid = true; 
        }
        else 
        {
            cout << displayError(8); 
        }
    }
    return num[0] - '0'; 

}

//============================================//
// Gets and sets player's name                //
//============================================//

Player askPlayerName(Player p, int a)
{

    string full;  
    bool isGoodSpace = false, firstChar = false; 
    int spaces = 0, beforeLetterSpace = 0, firstSpace = 0; 
    p.setPlayerNumber(a); 

    while ( !isGoodSpace ) 
    {   
        cout << "\nPlayer "<< p.getPlayerNumber();
        cout << ", enter your first and last name separated by space(s).\n";
        getLine(cin, full); 
        int f = len(full); 
        firstChar = false; 
        firstSpace = 0, beforeLetterSpace = 0, spaces = 0; 

        for ( int j = 0; j < f; j++ )
        {
            if ( full[j] == ' ' )
            {
                spaces += 1;
            }
            else if ( ( full[j] >= 'A' && full[j]  <= 'Z' ) || 
                 ( full[j] >= 'a' && full[j] <= 'z' ) )
            {
                if ( full[j-1] == ' ' && firstChar )
                {
                    beforeLetterSpace += 1;
                }
                if ( !firstChar ) 
                {
                    firstChar = true; 
                    if ( full[j-1] == ' ' )
                    {
                        firstSpace = 1; 
                    }
                }
            }
            else
            {
                cout << displayError(9); 
                break; 
            }
            
            if ( j == f - 1 ) 
            {
                if ( spaces > 0 && beforeLetterSpace - firstSpace <= NUM_NAMES - 1 && 
                     beforeLetterSpace + firstSpace  <= NUM_NAMES && beforeLetterSpace > 0 ) 
                {
                    isGoodSpace = true; 
                }
                else 
                {
                    cout << displayError(6);
                }
            }
        }
    }
    int f = len(full); 
    firstChar = false; 
    bool secondChar = false; 
    int idx = 0; 

    for ( int i = 0; i < f; i++ ) 
    {
        if ( !firstChar && full[i] != ' ')
        {
            toUpper(full[i]); 
            firstChar = true; 
            idx = i; 
        }
        else if( full[i-1] == ' ' && full[i+1] != ' ' && 
                 firstChar && !secondChar )
        {
            toUpper(full[i]);
            secondChar = true; 
        }
        else 
        {
            toLower(full[i]);
        }
    }
    p.setFirstName(full, idx); 
    p.setFullName(full); 
    return p; 

}

//============================================//
// Gets game board dimensions                 //
//============================================//

int getDimensions(int& N, int& M)
{

    string numRows, numCols; 
    int row, col; 
    bool isDimension = false, badChar; 
    cout << '\n'; 

    while ( !isDimension ) 
    {
        row = 0, col = 0; 
        badChar = false; 
        cout << "Please enter the dimensions of the board\n\n"; 
        cout << "Enter the number of rows    -> "; 
        cin >> numRows; 
        cout << "\nEnter the number of columns -> "; 
        cin >> numCols; 

        int maxRowLen = intLen(MAX_ROWS); 
        int maxColLen = intLen(MAX_COLUMNS); 
        int r = len(numRows); 
        int c = len(numCols); 

        if ( r <= 0 || r > maxRowLen || c <= 0 || c > maxColLen )
        {
            cout << displayError(5); 
        }
        else 
        {
            for ( int i = 0; i < r; i++)
            {
                if ( numRows[i] > '9' || numRows[i] < '0' )
                {
                    cout << displayError(2); 
                    badChar = true; 
                    break; 
                }
                row += ( numRows[i] - '0' ) * pow(10, r-i-1); 
            }

            for ( int i = 0; i < c; i++)
            {
                if ( numCols[i] > '9' || numCols[i] < '0' )
                {
                    cout << displayError(2); 
                    badChar = true; 
                    break; 
                }
                col += ( numCols[i] - '0' ) * pow(10, c-i-1); 
            }
            if ( row > MAX_ROWS || row < MIN_ROWS ||
                 col > MAX_COLUMNS || col < MIN_COLUMNS || badChar )
            {
                cout << displayError(10); 
            }
            else 
            {
                isDimension = true; 
            }
        }  
    }   
    N = row; 
    M = col; 
    return N*M; 

}

//============================================//
// Allows player to make a move               //
//============================================//

int makeMove(Player& p, int& N, int& M, int& NxM, char* board)
{

    string position;
    string f = p.getFirstName();  
    int l; 
    int coordinate = 0; 
    bool isNumber = false, inValid; 
    char piece = p.getPiece(); 

    while ( !isNumber )
    { 
        inValid = false; 
        cout << f << "(" << piece << ")'s turn: "; 
        cin >> position;
        toUpper(position[0]); 
        l = len(position); 
        int lenOfNxM = intLen(NxM);  
        int n = NxM; 

        if ( l > lenOfNxM + 1 || l < 2 || 
             position[0] < 'A' || position[0] > 'Z' )
        {
            cout << displayError(5); 
        }
        else 
        {
            coordinate = ( position[0] - 'A' ) * M; 
            int i = 1; 
            int sum = 0; 

            while ( i < l ) 
            {
                inValid = position[i] < '0' || position[i] > '9'; 
                if ( inValid )
                {
                    cout << displayError(2);
                    break; 
                }
                else 
                {
                    sum += ( position[i] - '0' ) * pow(10, l - i - 1); 
                }
                i += 1;
            }
            coordinate += sum; 

            if ( sum <= M && !inValid && board[coordinate-1] == ' ' ) 
            {
                isNumber = true; 
            }
            else 
            {
                cout << displayError(7); 
            }
        }
    }
    return coordinate-1; 

}

//============================================//
// Determines a player's turn                 //
//============================================//

int determineTurn(int& gameNumber, char& lastWinner, int& moves, int& num_players, char& lastMove, int& turn) 
{

    if ( ( gameNumber == 1 && moves == 0 ) || 
         ( ( lastWinner - 'a' ) + 1 >= num_players && moves == 0 ) || 
           ( lastMove - 'a' )  + 1 >= num_players ) 
    {
        return 0; 
    }
    else  
    {
        return ( PIECES[turn] - 'a' ) + 1; 
    }

}

//============================================//
// Displays proper error message              //
//============================================//

string displayError(int err)
{

    switch(err)
    {
        case 1: 
            return "\n\nPosition Error: Invalid position.\n\n"; 
        case 2: 
            return "\nInput Error: Invalid input.\n";
        case 3: 
            return "\n\nChoice Error: Invalid choice.\n\n"; 
        case 4: 
            return "\n\nSymbol Error. Invalid symbol. Input a number on the board.\n\n";
        case 5: 
            return "\nSize Error. Input doesn't match size needed.\n\n"; 
        case 6: 
            return "\nSpace Error. Spacing does not match specifications.\n"; 
        case 7: 
            return "\nSpot Error. Position restricted.\n\n";
        case 8: 
            return "\nNumber Error: Invalid number of players.\n\n";
        case 9: 
            return "\n\nCharacter Error. Only alphabetic characters and spaces allowed.\n\n"; 
        case 10: 
            return "\nDimension Error. Numerical Dimensions: 3x3 to 12x15\n\n"; 
        default: 
            return "\n\nUnknown Error\n\n";
    }

}

//============================================//
// Converts lowercase character to uppercase  //
//============================================//

void toUpper(char& c) 
{

    if ( c >= 'a' && c <= 'z' )
    {
        c = 'A' + c - 'a';
    }

}

//============================================//
// Converts uppercase character to lowercase  //
//============================================//

void toLower(char& c) 
{

    if ( c >= 'A' && c <= 'Z' )
    {
        c = 'a' + c - 'A';
    }

}

//============================================//
// Prints out Tic Tac Toe board               //
//============================================//

void printBoard(char* board, int& N, int& M) 
{

    cout << "\n   "; 

    for ( int i = 0; i < M; i++ ) 
    {
        if ( i <= 9 )
        {
            cout << " ";
        }
        cout << i+1 << "  ";
    }
    cout << endl << "   "; 

    for ( int l = 0; l < M; l++ )
    {
        cout << "--- "; 

    }
    cout << endl; 

    for (int j = 0; j < N; j++ ) 
    {
        cout << rows[j] << " ";

        for ( int k = 0; k < M; k++) 
        {
            cout << "| " << board[(j*M)+k] << " "; 
        }
        cout << "| " << rows[j] << endl; 
        cout << "   "; 

        for ( int m = 0; m < M; m++ ) 
        {
            cout << "--- "; 
        }
        cout << "\n";

    }
    cout << " "; 

    for ( int i = 0; i < M; i++ ) 
    {
        if ( i <= 9 ) 
        {
            cout << "   "; 
        }
        else
        {
            cout << "  "; 
        }

        cout << i+1;
    }
    cout << "\n\n";
}

//============================================//
// Clears the game board                      //
//============================================//

char* clearBoard(char* board, int& NxM)
{
    char* newBoard = new char[NxM]; 

    for (int i = 0; i < NxM; i++ ) 
    {
        newBoard[i] = ' '; 
    }
    return newBoard; 

}

//============================================//
// Finds length of longest name               //
//============================================//

int longestNameLength(Player players[], int num_players)
{
    
    int max_name_length = 0; 

    for ( int j = 0; j < num_players; j++ ) 
    {
        if ( len(players[j].getFullName()) > max_name_length )
        {
            max_name_length = len(players[j].getFullName()); 
        }
    }
    return max_name_length; 

}

//============================================//
// Prints the game statistics                 //
//============================================//

void printGameStats(Player* players, int num_players, int l, int gamesPlayed, int longest)
{
    cout << "Total games played = " << gamesPlayed;
    cout << endl; 
    cout << endl; 

    for ( int j = 0; j < longest; j++ )
    {
            cout << ' '; 
    }
    cout << " ------ ------ ------ " << endl; 

    for ( int j = 0; j < longest; j++ )
    {
            cout << ' '; 
    }
    cout << " | WIN | LOSS | DRAW|" << endl; 
    
    
    for ( int i = 0; i < num_players; i++ ) 
    {
        for ( int j = 0; j < longest; j++ )
        {
            cout << ' '; 
        }
        cout << " ------ ------ ------ " << endl; 
        cout << players[i].getFullName(); 
        
        for ( int j = 0; j < longest-len(players[i].getFullName()); j++ )
        {
            cout << ' '; 
        }
        cout << " |    " << players[i].getWins(); 
        cout << "|    " << players[i].getLosses(); 
        cout << " |    " << players[i].getDraws(); 
        cout << "|" << endl; 

    }

    for ( int j = 0; j < longest; j++ )
    {
            cout << ' '; 
    }
    cout << " ------ ------ ------ \n\n"; 

}

//============================================//
// Adds a win, loss, or draw to players       //
//============================================//

void addWinLossDraw(Player* players, int num_players, int turn, int isDraw)
{

    if ( isDraw )
    {
        for ( int i = 0; i < num_players; i++ )
        {
            players[i].addStat(0); 
        }
    }
    else 
    {
        for ( int j = 0; j < num_players; j++ )
        {
            if ( turn == j )
            {
                players[j].addStat(1); 
            }
            else 
            {
                players[j].addStat(-1); 
            }
        }
    }
}

//============================================//
// Finds winning combination, if it exists    //
//============================================//

char* detectWin(char* board, int& M, int& NxM, bool& win)
{

    for ( int i = 0; i < NxM; i++ )
    {
        if ( board[i] >= 'a' && board[i] <= 'e' )
        {
            if ( board[i] == board[i+1] &&
                 board[i+1] == board[i+2] && 
                 i != ( ( ( i + M ) / M ) * M  - 1 ) && 
                 i != ( ( ( i + M ) / M ) * M  - 2 ) ) 
            {
                toUpper(board[i]); 
                toUpper(board[i+1]);
                toUpper(board[i+2]);
                win = !win; 
                return board; 
            }

            if ( board[i] == board[i + ( 1 * M )] && 
                 board[i + ( 1 * M )] == board[i + ( 2 * M )] ) 
            {
                toUpper(board[i]); 
                toUpper(board[i + ( 1 * M )]);
                toUpper(board[i + ( 2 * M )]); 
                win = !win; 
                return board; 
            } 
        }  
    }

    for ( int i = 0; i < NxM; i++ )
    {
        if ( board[i] >= 'a' && board[i] <= 'e' )
        {
            if ( board[i] == board[i + 1 + ( M * 1 )] && 
                 board[i + 1 + ( M * 1 )] == board[i + 2 + ( M * 2 )] )
            {
                toUpper(board[i]); 
                toUpper(board[i + 1 + ( M * 1 )]);
                toUpper(board[i + 2 + ( M * 2 )]); 
                win = !win; 
                return board; 
            }

            if ( board[i] == board[i + ( M * 1 ) - 1] && 
                 board[i + ( M * 1 ) - 1] == board[i + ( M * 2 ) - 2] )
            {
                toUpper(board[i]); 
                toUpper(board[i + ( M * 1 ) - 1]); 
                toUpper(board[i + ( M * 2 ) - 2]); 
                win = !win; 
                return board; 
            }
        }
    }
    return board; 

}

//============================================//
// Asks the player if they want to play again //
//============================================//

bool endGame() 
{

    string option; 
    bool isOption = false;
    cin.ignore(1);

    while ( !isOption )
    {
        cout << "Would you like to play again? Type y or n.\n\n"; 
        getLine(cin, option);
        int l = len(option); 

        if ( l > 1 )
        {
            cout << displayError(5);
        }
        else
        {
            toLower(option[0]); 
            if ( option[0] == 'y' || option[0] == 'n' )
            {
                isOption = true; 
            }   
            else 
            {
                cout << displayError(2) << "\n";  
            }
        }

    }
    return option == "n";

}

//============================================//
// Returns a base to a power                  //
//============================================//

int pow(int base, int exponent)
{

    if ( base == 0 )
    {
        return 0; 
    }
    if ( base == 1 || exponent == 0 )
    {
        return 1; 
    }
    if ( exponent == 1 )
    {
        return base; 
    }
    else
    {
        int powerSum = 0; 
        while ( exponent > 1 ) 
        {
            powerSum += base; 
            exponent -= 1; 
        }
        base = powerSum; 
    } 
    return base; 

}

//============================================//
// Returns length of an integer               //
//============================================//

int intLen(int i) 
{

    int j = 1; 

    while ( i > 10 ) 
    {
        i /= 10;
        j += 1; 
    }
    return j; 

}

//============================================//
// Returns length of a string                 //
//============================================//

int len(string s)
{

    int i = 0; 

    while ( s[i] != '\0' )
    {
        i += 1; 
    }
    return i; 

}

//============================================//
// Takes user input and stores it in a string //
//============================================//

istream& getLine(istream& is, string& r)
{   
    char next;  
    r = ""; 

    while ( is.get(next) && next != '\n' ) 
    {
        r.push_back(next); 
    }
    return is; 

}