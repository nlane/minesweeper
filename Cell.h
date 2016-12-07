#ifndef _Cell_H // must be unique name in the project
#define _Cell_H

#include <stdio.h>
#include <stdlib.h>

class Cell {
    int row;
    int col;
    
    
  public:
    bool opened;
    bool hasMine;
    int numMines;
    Cell();
    void assignIJ(int i, int j);
    int assignMine();
    void addSurroundingMine();
    void openCell();
    char printCell(bool gameOver);
    
};

#endif