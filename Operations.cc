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


bool Operations::isValid(Grid &theGrid, int x, int y, int rotation){

    // edges

    if (x==0 && y==0 && rotation==0){
        for (int r=0; r<4; ++r){
            for (int c=0; c<4; ++c){
                int bY = theGrid.current->getY()+r;
                int bX = theGrid.current->getX()+c;
                char value = theGrid.current->getBlock()[theGrid.current->getRotate()][r][c];
                if (value!='.'){
                    if (bY <0 || bY >= theGrid.height || 
                    bX < 0 || bX>=theGrid.width){
                        return false;
                    }
                    if (theGrid.mainGrid[bY][bX].isOccupied()){
                        return false;
                    }
                }
            }
        }
        return true;
    }

    int rotate = (theGrid.current->getRotate()+rotation)%4;

    for (int r=0; r<4; ++r){
        for (int c=0; c<4; ++c){
            char value = theGrid.current->getBlock()[rotate][r][c];
            int bY = theGrid.current->getY() + y +r;
            int bX = theGrid.current->getX() + x + c;

            if (value != '.'){

                if (bY < 0 || bY >= theGrid.height || 
                bX < 0 || bX >= theGrid.width){
                    return false;
                }

                if (theGrid.mainGrid[bY][bX].isOccupied()){

                    if (bY < theGrid.current->getY() ||
                    bY > theGrid.current->getY()+3 ||
                    bX < theGrid.current->getX() ||
                    bX > theGrid.current->getX()+3){
                        return false;
                    }

                    if (theGrid.current->getBlock()[theGrid.current->getRotate()][r+y][c+x] == '.'){
                        return false;
                    }
                }
            }
        }
    }
    return true;
}
