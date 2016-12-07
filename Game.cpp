#include <iostream>
#include "Cell.h"
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//valgrind -v ./blah -w 1 -m 1 -h 2 

using namespace std;

bool gameOver = false;
int boardWidth = 8;
int boardHeight = 8;
int cellsLeft;
int numMines = 0;
int maxNumMines = 10;

// I = X = Height
// J = Y = Width


// Adds count to surrounding cells
void addSurroundingMineCounts(Cell** board, int newMineI, int newMineJ) {
    if (newMineI > 0) {
        board[newMineI-1][newMineJ].addSurroundingMine();
        if (newMineJ > 0) {
            board[newMineI-1][newMineJ-1].addSurroundingMine();
        }
        if (newMineJ < (boardWidth - 1)) {
            board[newMineI-1][newMineJ+1].addSurroundingMine();
        }
    }
    if (newMineI < (boardHeight-1)) {
        board[newMineI + 1][newMineJ].addSurroundingMine();
        if (newMineJ > 0) {
            board[newMineI+1][newMineJ-1].addSurroundingMine();
        }
        if (newMineJ < (boardWidth - 1)) {
            board[newMineI+1][newMineJ+1].addSurroundingMine();
        }
    }
    if (newMineJ > 0) {
        board[newMineI][newMineJ-1].addSurroundingMine();
    }
    if (newMineJ < (boardWidth - 1)) {
        board[newMineI][newMineJ+1].addSurroundingMine();
    }
}

// Generates 2D array of Cells then randomly assigns bombs to it, returns board
Cell** generateBoard(){
    Cell** board;
    board = new Cell*[boardHeight];
    for (int i = 0; i < boardHeight; i++) {
        board[i] = new Cell[boardWidth];
    }
    
    for (int i = 0; i < boardHeight; i++) {
        for (int j = 0; j < boardWidth; j++) {
            board[i][j].assignIJ(i,j);
        }
    }
    srand(time(NULL));
    while (numMines < maxNumMines) {
        int newMineI = rand() % boardHeight;
        int newMineJ = rand() % boardWidth;
        int newMine = board[newMineI][newMineJ].assignMine();
        if (newMine == 1) {
            numMines ++;
            addSurroundingMineCounts(board, newMineI, newMineJ);
        }
    }
    return board;
}

// Checks to see if cell is a bomb, if so then game is over
// If not it checks if it has any neighboring empty spaces, then acts accordingly
void open(int i, int j, Cell** board){
    // first check if these are valid integers within board range
    if(i < 0 or i >= boardHeight or j < 0 or j >= boardWidth){
        //cout << "Please enter a valid coordinate\n";
        return;
    }
    //is this cell already opened?
    if(board[i][j].opened){
        //cout << "This space was already opened\n";
        return;
    }
    //if not, open it
    else{
        board[i][j].openCell();
        cellsLeft--;
    }
    
    //is this cell a bomb?
    if(board[i][j].hasMine){
        gameOver = true;
        cout << "You lose. Sucks to suck tbh." << endl;
        return;
    }
    
    
    
    //Check if all non-mine cells are open
    if(cellsLeft == 0){
        gameOver = true;
        cout << "YOU WIN!\n";
        return;
    }
    
    //does this cell have numMines == 0? 
    //Then call open on all 8 neighbors
    else if(board[i][j].numMines == 0){
        open(i-1, j-1, board);
        open(i-1, j, board);
        open(i-1, j+1, board);
        open(i, j-1, board);
        open(i, j+1, board);
        open(i+1, j-1, board);
        open(i+1, j, board);
        open(i+1, j+1, board);
    }
    
}

// Gets user input to determine next move, calls open on the given coords
void nextMove(Cell** board){
    int i;
    int j;
    cout << "Please enter a row: ";
    cin >> i;
    cout << "Please enter a column: ";
    cin >> j;
    cout << "You opened cell: " << i << ", " << j << "\n\n";
    open(i, j, board);
}

void printBoard(Cell** board){
    //FYI: Beginner (8x8, 10 mines), Intermediate (16x16, 40 mines) and Expert (24x24, 99 mines).
    for (int j = -1 ; j < boardWidth; j++) {
        if (j == -1) {
            cout <<" " << "\t";
        }
        else {
            cout << j << "\t";
        }
    }
    cout << endl << endl;
    for(int i = 0; i < boardHeight; i++){
        for(int j = -1; j < boardWidth; j++){
            if (j == -1) {
                cout << i << "\t";
            }
            else {
                cout << board[i][j].printCell(gameOver) << "\t";
            }
        }
        cout << endl;
    }
}


int main(int argc, char** argv) {
    for (int i = 1; i < argc - 1; i+=2) {
        if (strlen(argv[i])==2) {
            if (strncmp(argv[i], "-w", 2) == 0) {
                boardWidth = atoi(argv[i+1]);
            } else if (strncmp(argv[i], "-h", 2) == 0) {
                boardHeight = atoi(argv[i+1]);
            } else if (strncmp(argv[i], "-m", 2) == 0) {
                maxNumMines = atoi(argv[i+1]);
            } 
        } else if (strlen(argv[i]) == 6) {
            if (strncmp(argv[i], "-width", 6) == 0) {
                boardWidth = atoi(argv[i+1]);
            } else if (strncmp(argv[i], "-mines", 6) == 0) {
                maxNumMines = atoi(argv[i+1]);
            }
        } else if (strlen(argv[i]) == 7) {
            if (strncmp(argv[i], "-height", 7) == 0) {
                boardHeight = atoi(argv[i+1]);
            }
        }
    }
    if (maxNumMines > boardWidth * boardHeight) {
        cout<<"Too Many Mines, please enter new parameters." << endl;
        return 0;
    }
    if (boardHeight > 19 || boardWidth > 19) {
        cout<<"Too large of a board, please enter new parameter.  The max size is 19x19." << endl;
        return 0;
    }
    cellsLeft = (boardWidth * boardHeight) - maxNumMines;
    Cell** board = generateBoard();
    while(!gameOver){
        printBoard(board);
        nextMove(board);
    }
    printBoard(board);
    for (int i = 0; i < boardHeight; i++) {
        delete[] board[i];
    }
    delete[] board;
    return 0;
}