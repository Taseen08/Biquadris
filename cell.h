#ifndef CELL_H
#define CELL_H
#include "subject.h"
#include "observer.h"

class Board;

class Cell : public Subject {
    int x;
    int y;
    bool occupied;
    char state;
    Board *mainBoard;
    public:
        Cell(int x, int y,Board *mainBoard,bool occupied=false, char state='.');
		void notifyObservers() override;
		void setX(int x);
		void setY(int y);
		int getX();
		int getY();
        bool isOccupied();
        char getState();
        void setState(char myState);
        void unsetState();
        Board* getBoard();
};

#endif