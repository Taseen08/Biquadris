#ifndef GRID_H_
#define GRID_H_
#include <vector>
#include <string>
#include <iostream>
#include "cell.h"
#include "block.h"
#include "textdisplay.h"
#include "Level.h"
#include "laidBlocks.h"
#include "observer.h"
#include "Operations.h"

class TextDisplay;
class laidBlocks;
class Operations;

class Grid : public Subject{
    int height;
    int width;
    int score;
    int highScore;
    int level;
    int player;
    bool heavy;
    bool force;
    bool blind;
    std::vector<std::vector<Cell> > mainGrid;
    std::vector<std::vector<laidBlocks> > lyingBlocks;
    Block *next;
    Block *current;
    Level *currentLevel;
    bool dead;
    bool effect;
    // notification attr missing

    public:
        Grid(int width, int height, int level, int player);
        void init();
        int getWidth();
        int getHeight();
        int getScore() const;
        void setObserver(Observer *ob);
        void notifyObservers() override;
        void activateCell(int x, int y, char state);// setPiece
        void deactivateCell(int x, int y); // unsetPiece
        void findLyingBlock(int lev); // restBlock
        void deactivateBlock();
        void reset();
        void setCurrentBlock(Block *currentBlock);
        void setNextBlock(Block * nextBlock);
        Block* getCurrentBlock();
        Block* getNextBlock();
        Level* getCurrentLevel();
        int getLevel();
        void deactivateBlock(); // unsetBlock
        void setCurrentLevel(int level, bool random, string file = ""); 
        int getPlayer();
        bool isBlind() const;
        void setBlind(bool blind);
        bool isHeavy(bool heavy) const;
        void setHeavy(bool heavy);
        bool isForce() const; //returns whether board has force active
        void setForce(bool force); //sets whether board has force active
		bool isEffect() const; //returns whether effect is needed
		void setEffect(bool effectNeeded); //sets whether effect is needed
        int getHighScore();
        void setHighScore(int highScore);
        void setDead(bool dead); //sets whether player is dead
		bool getDead(); //returns whether player is dead
        const std::vector<std::vector<Cell> >& getGrid();
        friend class Operations;
        friend ostream &operator<<(ostream &out, const Grid &grid);
        ~Grid();

};

#endif