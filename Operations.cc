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


void Operations::removeLines(Grid &theGrid){
    int s = theGrid.lyingBlocks.size();
    Block *current = theGrid.current;
    // if (theGrid.lyingBlocks[s-1][0].getLevelGen() == 4){
    //     if (current->getShape() != "*"){

    //     } 
    // } // level 4 shit

    int removedLines = 0;

    for (int r=0; r<4; ++r){
        if (current->getY()+r < theGrid.height){
            bool existLine = true;
            for (int c = 0; c< theGrid.width; ++c){
                if (theGrid.mainGrid[current->getY()+r][c].isOccupied()==false){
                    existLine = false;
                    break;
                }
            }

            if (existLine){

                int moveVal = current->getY()+r;

                for (int i=theGrid.lyingBlocks.size()-1; i>=0; --i){
                    bool canRemove = false;

                    for (int j=0; j<4; ++j){
                        if (theGrid.lyingBlocks[i][j].getCoord() == moveVal){
                            theGrid.lyingBlocks[i][j].setOccupied(true);
                        }

                        if (theGrid.lyingBlocks[i][j].getOccupied()==false){
                            canRemove = false;
                        }

                        if (theGrid.lyingBlocks[i].size()==1){
                            break;
                        }
                    }

                    if (canRemove==true){
                        int level = theGrid.lyingBlocks[i][0].getLevelGen();
                        theGrid.score += (1+level) * (1 + level);
                        // theGrid.notifications.scoreChanged = true;
                        theGrid.setPointsModified(true);
                        theGrid.notifyObservers();
                        theGrid.lyingBlocks.erase(theGrid.lyingBlocks.begin()+i);
                    }
                }

                for (int row=moveVal-1; row>0; --row){
                    for (int col = 0; col < theGrid.width; ++col){
                        if (theGrid.mainGrid[row][col].isOccupied()){
                            theGrid.mainGrid[row+1][col].setState(theGrid.mainGrid[row][col].getState());
       
                        }
                        else {
                            theGrid.mainGrid[row+1][col].unsetState();
                        }
                    }
                }

                for (int row=0; row<theGrid.width; ++row){
                    theGrid.mainGrid[0][row].unsetState();
                }

                removedLines+=1;
            }
        }
    }

    if (removedLines>0){

        for (int row = 0; row<s; ++row){
            for (int col =0; col<4; ++col){
                theGrid.mainGrid[row][col].setY(theGrid.lyingBlocks[row][col].getCoord()+removedLines);
                if (theGrid.lyingBlocks[row].size() ==1){
                    break;
                }
            }
        }

        theGrid.score += (theGrid.level + removedLines) * (theGrid.level + removedLines);
        // notifications.scoreChanged = true;
        theGrid.setPointsModified(true);

        theGrid.notifyObservers();

        // level 4
        // if (theGrid.level == 4)


    }

    if (removedLines >=2){
        theGrid.effect = true;
    }

    delete theGrid.current;


}