#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;
//{
    //AI notes: Makes a list of all the possible moves and rates them based on criteria (exposure, gain, protection, finishing, power, imminent threat)
    //Each piece has a weight which helps determine the value of a move
    //Exposure is a measure of how exposed or vulnerable a piece becomes as a result of making a move
    //Gain is a measure of how much a move would benefit the AI immediately (taking another piece, promotion)
    //Protection is a measure of how protected a piece is based on where it is or would move; a king being castled is more protected than a king alone
    //Finishing is a measure of, given the current board, how many moves away a check mate could be, and whether a given move brings the game closer to an end
    //Power is a measure of how much influence the AI has over the board due to a certain move; having a highly mobile piece in the center is more powerful than a corner
    //Imminent threat evaluates the loss of any pieces within the next turn
    //The value given to a move is a function of the value of the position a piece currently has; if a pawn is in danger, but a tower can be taken safely, taking the rook might be the larger point differential (depending on parameters)
    //The AI always choses the move with the greatest value increase
    //The value of a piece in a square is a function of the piece, square, and board setup (a bishop right in front of the king is useless, but a tower in the same spot is powerful)
    //Put more ideas for AI design here

    //Find solution for differentiating black and white pieces
    //Pieces have a position, and possible moves array of the coordinates of the places they can move to
    //En passant kill
    //Pawns have a special promote function, which changes the piece to a chosen piece when it reaches the end
//}

//On the broad level, we have pieces and spaces

//Pieces have position (which can be used to access spaces)
//color, which identifies the side they belong to
//moves array
//and code, initialized by the specific piece's constructor

//spaces have pieces, pointed at by a pointer and
//an occupied bool, so we dont try and access a space that isn't occupied

class pieces{
public:
    int position;
    int color;
    // int moves[];
    int code;
};

class space{
public:
    bool isOccupied;
    pieces *piece;
    space(){
        isOccupied = false;
    }
};

class pawn: public pieces{
public:
    pawn(){
        code = (int) 'p';
    }
    //represented by a *
};

class knight: public pieces{
public:
    knight(){
        code = (int) 'k';
    }
    //represented by a 4
};

//Castling
class tower: public pieces{
public:
    tower(){
        code = (int) 't';
    }
    //represented by a T
};

class bishop: public pieces{
public:
    bishop(){
        code = (int) 'b';
    }
    //represented by a ~
};

class queen: public pieces{
public:
    queen(){
        code = (int) 'q';
    }
    //Represented by an @
};

//King has a a special check and check-mate status
class king: public pieces{
public:
    king(){
        code = 0;
    }
    //Represented by a $
};

class Board{
    
    //One instance of a 8x8 chess board.
    //Information arrangements: White pieces, black pieces
    //functions: print (shows the board and the graveyards on both sides), select (takes a coordinate, and if theres a pieces there on your side, highlights the possible moves)
    //cont... which (takes a coordinate and prints the type of piece at that coordinate)
    //Need to keep an array of all possible moves, such that we can tell when a board is locked
    

public:
    pawn w_pawn[8];
    knight w_knight[2];
    bishop w_bishop[2];
    tower w_tower[2];
    queen w_queen;
    king w_king;

    pawn b_pawn[8];
    knight b_knight[2];
    bishop b_bishop[2];
    tower b_tower[2];
    queen b_queen;
    king b_king;

    space gameBoard[8][8];

    int printBoard();
    int printSelect(int sel);

    Board(){
        for(int i = 0; i < 8; i++){
            w_pawn[i].position = (i + 10);
            w_pawn[i].color = (int) 'w';
            gameBoard[1][i].isOccupied = true;
            gameBoard[1][i].piece = &w_pawn[i];
        }

        w_tower[0].position = 00;
        w_tower[0].color = (int) 'w';
        gameBoard[0][0].isOccupied = true;
        gameBoard[0][0].piece = &w_tower[0];
        
        w_tower[1].position = 07;
        w_tower[1].color = (int) 'w';
        gameBoard[0][7].isOccupied = true;
        gameBoard[0][7].piece = &w_tower[1];

        w_knight[0].position = 01;
        w_knight[0].color = (int) 'w';
        gameBoard[0][1].isOccupied = true;
        gameBoard[0][1].piece = &w_knight[0];

        w_knight[1].position = 06;
        w_knight[1].color = (int) 'w';
        gameBoard[0][6].isOccupied = true;
        gameBoard[0][6].piece = &w_knight[1];

        w_bishop[0].position = 02;
        w_bishop[0].color = (int) 'w';
        gameBoard[0][2].isOccupied = true;
        gameBoard[0][2].piece = &w_bishop[0];

        w_bishop[1].position = 05;
        w_bishop[1].color = (int) 'w';
        gameBoard[0][5].isOccupied = true;
        gameBoard[0][5].piece = &w_bishop[1];

        w_queen.position = 03;
        w_queen.color = (int) 'w';
        gameBoard[0][3].isOccupied = true;
        gameBoard[0][3].piece = &w_queen;

        w_king.position = 04;
        w_king.color = (int) 'w';
        gameBoard[0][4].isOccupied = true;
        gameBoard[0][4].piece = &w_king;

        for(int i = 0; i < 8; i++){
            b_pawn[i].position = (i + 60);
            b_pawn[i].color = (int) 'b';
            gameBoard[6][i].isOccupied = true;
            gameBoard[6][i].piece = &b_pawn[i];
        }

        b_tower[0].position = 70;
        b_tower[0].color = (int) 'b';
        gameBoard[7][0].isOccupied = true;
        gameBoard[7][0].piece = &b_tower[0];

        b_tower[1].position = 77;
        b_tower[1].color = (int) 'b';
        gameBoard[7][7].isOccupied = true;
        gameBoard[7][7].piece = &b_tower[1];

        b_knight[0].position = 71;
        b_knight[0].color = (int) 'b';
        gameBoard[7][1].isOccupied = true;
        gameBoard[7][1].piece = &b_knight[0];

        b_knight[1].position = 76;
        b_knight[1].color = (int) 'b';
        gameBoard[7][6].isOccupied = true;
        gameBoard[7][6].piece = &b_knight[1];

        b_bishop[0].position = 72;
        b_bishop[0].color = (int) 'b';
        gameBoard[7][2].isOccupied = true;
        gameBoard[7][2].piece = &b_bishop[0];

        b_bishop[1].position = 75;
        b_bishop[1].color = (int) 'b';
        gameBoard[7][5].isOccupied = true;
        gameBoard[7][5].piece = &b_bishop[1];

        b_queen.position = 73;
        b_queen.color = (int) 'b';
        gameBoard[7][3].isOccupied = true;
        gameBoard[7][3].piece = &b_queen;

        b_king.position = 74;
        b_king.color = (int) 'b';
        gameBoard[7][4].isOccupied = true;
        gameBoard[7][4].piece = &b_king;

    }
};

int Board::printBoard(){
    cout << endl;
    cout << "   a     b     c     d     e     f     g     h   " << endl;
    cout << " _____ _____ _____ _____ _____ _____ _____ _____ " << endl;
    for(int i = 7; i > -1; i--){
        cout << "|     |     |     |     |     |     |     |     |" << endl;
        for(int j = 0; j < 8; j++){
            if(gameBoard[i][j].isOccupied){
                switch(gameBoard[i][j].piece->color + gameBoard[i][j].piece->code){
                case (int)('b' + 'p'):
                    cout << "|  *  ";
                    break;
                case (int)('w' + 'p'):
                    cout << "|  +  ";
                    break;
                case (int)('b' + 't'):
                    cout << "|  t  ";
                    break;
                case (int)('w' + 't'):
                    cout << "|  T  ";
                    break;
                case (int)('b' + 'k'):
                    cout << "|  4  ";
                    break;
                case (int)('w' + 'k'):
                    cout << "|  r  ";
                    break;
                case (int)('b' + 'b'):
                    cout << "|  -  ";
                    break;
                case (int)('w' + 'b'):
                    cout << "|  ~  ";
                    break;
                case (int)('b' + 'q'):
                    cout << "|  @  ";
                    break;
                case (int)('w' + 'q'):
                    cout << "|  Q  ";
                    break;
                case (int)('b'):
                    cout << "|  $  ";
                    break;
                case (int)('w'):
                    cout << "|  S  ";
                    break;
                }
            }
            else{
                cout << "|     ";
            }
        }
        cout << "|  " << i +1 << endl;
        cout << "|_____|_____|_____|_____|_____|_____|_____|_____|" << endl;
    }
    cout << endl;
    cout << "   a     b     c     d     e     f     g     h   " << endl;
    cout << endl;
}

int Board::printSelect(int sel){
    int row = sel/10;
    cout << row << endl;
    int col = sel%10;
    cout << col << endl;
    cout << endl;
    cout << "   a     b     c     d     e     f     g     h   " << endl;
    cout << " _____ _____ _____ _____ _____ _____ _____ _____ " << endl;
    for(int i = 23; i > -1; i--){
        if((i%3 == 2)){
            for(int j = 0; j <8; j++){
                if((j == col) && (i/3 == row)){
                    cout << "|xxxxx";
                }
                else{
                    cout << "|     ";
                }
            }
            cout << "|" << endl;
        }
        else if(i%3 == 1){
            for(int j = 0; j < 8; j++){
                if(gameBoard[i/3][j].isOccupied){
                    if((j == col) && (i/3 == row)){
                        switch(gameBoard[i/3][j].piece->color + gameBoard[i/3][j].piece->code){
                        case (int)('b' + 'p'):
                            cout << "|x * x";
                            break;
                        case (int)('w' + 'p'):
                            cout << "|x + x";
                            break;
                        case (int)('b' + 't'):
                            cout << "|x t x";
                            break;
                        case (int)('w' + 't'):
                            cout << "|x T x";
                            break;
                        case (int)('b' + 'k'):
                            cout << "|x 4 x";
                            break;
                        case (int)('w' + 'k'):
                            cout << "|x r x";
                            break;
                        case (int)('b' + 'b'):
                            cout << "|x - x";
                            break;
                        case (int)('w' + 'b'):
                            cout << "|x ~ x";
                            break;
                        case (int)('b' + 'q'):
                            cout << "|x @ x";
                            break;
                        case (int)('w' + 'q'):
                            cout << "|x Q x";
                            break;
                        case (int)('b'):
                            cout << "|x $ x";
                            break;
                        case (int)('w'):
                            cout << "|x S x";
                            break;
                        }
                    }
                    else{
                        switch(gameBoard[i/3][j].piece->color + gameBoard[i/3][j].piece->code){
                        case (int)('b' + 'p'):
                            cout << "|  *  ";
                            break;
                        case (int)('w' + 'p'):
                            cout << "|  +  ";
                            break;
                        case (int)('b' + 't'):
                            cout << "|  t  ";
                            break;
                        case (int)('w' + 't'):
                            cout << "|  T  ";
                            break;
                        case (int)('b' + 'k'):
                            cout << "|  4  ";
                            break;
                        case (int)('w' + 'k'):
                            cout << "|  r  ";
                            break;
                        case (int)('b' + 'b'):
                            cout << "|  -  ";
                            break;
                        case (int)('w' + 'b'):
                            cout << "|  ~  ";
                            break;
                        case (int)('b' + 'q'):
                            cout << "|  @  ";
                            break;
                        case (int)('w' + 'q'):
                            cout << "|  Q  ";
                            break;
                        case (int)('b'):
                            cout << "|  $  ";
                            break;
                        case (int)('w'):
                            cout << "|  S  ";
                            break;
                        }
                    }
                }
                else{
                    cout << "|     ";
                }
            }
            cout << "|  " << (i/3) +1 << endl;
        }
        else{
            for(int j = 0; j<8; j++){
                if((j == col) && (i/3 == row)){
                    cout << "|xxxxx";
                }
                else{
                    cout << "|_____";
                }
            }
            cout << "|" << endl;
        }
    }
    cout << endl;
    cout << "   a     b     c     d     e     f     g     h   " << endl;
    cout << endl;
}


int convertSpace(string input){
    if(input.size() != 2){
        return -1;
    }
    int column = (int) input[0];
    //A is 65, H is 72, a is 97, h is 104
    int row = input[1] - 1;
    if((row < 48) || (row > 55)){
        return -1;
    }
    else{
        row = row - 48;
    }
    if((column >= 97) && (column < 105)){
        column = column - 97;
    }
    else if((column >= 65) && (column < 73)){
        column = column - 65;
    }
    else{
        return -1;
    }
    return (column + (10*row));
}

int main(){
    Board game;
    game.printSelect(00);
}

//Value of the piece codes
//{
    // cout << "The value of 'b + p' is: " << (int)('b' + 'p') << endl;
    // cout << "The value of 'w + p' is: " << (int)('w' + 'p') << endl;
    // cout << "The value of 'b + t' is: " << (int)('b' + 't') << endl;
    // cout << "The value of 'w + t' is: " << (int)('w' + 't') << endl;
    // cout << "The value of 'b + k' is: " << (int)('b' + 'k') << endl;
    // cout << "The value of 'w + k' is: " << (int)('w' + 'k') << endl;
    // cout << "The value of 'b + b' is: " << (int)('b' + 'b') << endl;
    // cout << "The value of 'w + b' is: " << (int)('w' + 'b') << endl;
    // cout << "The value of 'b + q' is: " << (int)('b' + 'q') << endl;
    // cout << "The value of 'w + q' is: " << (int)('w' + 'q') << endl;
    // cout << "The value of 'b' is: " << (int)('b') << endl;
    // cout << "The value of 'w' is: " << (int)('w') << endl;
//}

//To do:
//Implement input/output
//Create parser function
//Make a which function
//Create function to populate moves list
    //Handle special moves (double pawn advance, pawn promotion...
    //Castling, and en passant)
    //Make an function to detect checks and checkmate
//Create function which shows moves for selected piece
//Add print of graveyard
//Make function to move pieces (force players to move king on check)
//Make function to detect when there are no moves
    //(simply return -1 if no move for a piece, if all pieces have no moves)