#include "Operations.h"
#include "grid.h"

void Operations::moveBlock(Grid &theGrid, int x, int y, int rotation){
    theGrid.deactivateBlock();

    int degree = (theGrid.current->getRotate()+rotation)%4;

    for (int r =0; r<4; ++r){
        for (int c=0; c<4; ++c){

            char val = theGrid.current->getBlock()[degree][r][c];
            int bY = theGrid.current->getY() + y + r;
            int bX = theGrid.current->getX() + x + c;

            if (val != '.'){
                theGrid.mainGrid[bY][bX].setState(val);
            }

        }
    }
    int newX = theGrid.current->getX()+x;
    int newY = theGrid.current->getY()+y;
    theGrid.current->setX(newX);
    theGrid.current->setY(newY);
    theGrid.current->setRotate(degree);
    
}
