#ifndef CELL_H
#define CELL_H
#include "subject.h"
#include "observer.h"

class Grid;

class Cell : public Subject {
    int x;
    int y;
    bool occupied;
    char state;
    Grid *mainBoard;
    public:
        Cell(int x, int y,Grid *mainBoard,bool occupied=false, char state='.');
		void notifyObservers() override;
		void setX(int x);
		void setY(int y);
		int getX();
		int getY();
        bool isOccupied() const;
        char getState() const;
        void setState(char myState);
        void unsetState();
        Grid* getGrid();
};

#endif