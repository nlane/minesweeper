#include "Cell.h"
#include <stdio.h>
#include <stdlib.h>

    // Constructor: takes in coords and initializes every other parameter to false/0
    Cell::Cell(){
        row = 0;
        col = 0;
        opened = false;
        hasMine = false;
        numMines = 0;
    }
    
    void Cell::assignIJ(int i, int j){
        row = i;
        col = j;
    }
    
    // Marks this cell as having mine
    int Cell::assignMine(){
        if (!hasMine) {
            hasMine = true;
            return 1;
        }
        return 0;
    }
    
    // A mine around this cell was added
    void Cell::addSurroundingMine(){
        if (!hasMine) {
            numMines++;
        }
    }
    
    // We opened cell
    void Cell::openCell(){
        opened = true;
    }
    
    // Call this when we want to print this cell
    char Cell::printCell(bool gameOver){
        if(opened || gameOver){
            if(hasMine){
                return '*';
            }
            else if(numMines == 0){
                return ' ';
            }
            else{
                return '0' + numMines;
            }
        }
        else{
            return '-';
        }
    }
