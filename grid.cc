#include <vector>
#include <iostream>
#include "cell.h"
#include "grid.h"
#include "textdisplay.h"
#include "block.h"
#include "OneLev.h"
#include "ZeroLev.h"

class laidBlocks;

void Grid::setObserver(Observer *ob){
    this->attach(ob);
    for (int i=0; i<this->height; ++i){
        for (int j=0; j<this->width; ++j){
            this->mainGrid[i][j].attach(ob);
        }
    }
}

void Grid::notifyObservers(){
    for (auto &ob : observers) ob->notify(*this);
}

Grid::~Grid(){
    delete this->current;
    delete this->next;
    delete this->currentLevel;
}

void Grid::init(){
    if (this->mainGrid.size() != 0){
        this->mainGrid.clear();
    }
    for (int r=0; r < this->height; ++r){
        std::vector<Cell> row;
        
        for (int c=0; c<this->width; ++c){
            row.emplace_back(Cell(r,c,this));
        }
        this->mainGrid.emplace_back(row);
    }
}

Grid::Grid(int width, int height, int level, int player){
    this->width = width;
    this->height = height;
    this->level = level;
    this->player = player;
    this->highScore = 0;
    this->blind = false;
    this->score = 0;
    this->heavy = false;
    this->force = false;
    this->dead = false;
    this->effect = false;
    this->current = nullptr;
    this->next = nullptr;
    this->currentLevel = nullptr;
    this->init();
}

int Grid::getScore() const{
    return this->score;
}
Block* Grid::getCurrentBlock(){
    return this->current;
}

void Grid::setCurrentBlock(Block *currentBlock){
    this->current = currentBlock;
}

Block* Grid::getNextBlock(){
    return this->next;
}

void Grid::setNextBlock(Block* nextBlock){
    this->next = nextBlock;
    this->notifyObservers(); // can set it after or could be modified
}

Level* Grid::getCurrentLevel(){
    return this->currentLevel;
}

bool Grid::isBlind() const{
    return this->blind;
}

int Grid::getPlayer(){
    return this->player;
}

int Grid::getLevel(){
    return this->level;
}

void Grid::setBlind(bool blind){
    this->blind = blind;
    notifyObservers();
}

bool Grid::isEffect() const{
    return this->effect;
}

void Grid::setEffect(bool eff){
    this->effect = eff;
}

void Grid::setHeavy(bool heavy){
    this->heavy = heavy;
}

bool Grid::isHeavy() const{
    return this->heavy;
}

bool Grid::isForce() const{
    return this->force;
}

void Grid::setForce(bool force){
    this->force = force;
}

void Grid::setHighScore(int high){
    this->highScore = high;
    this->notifyObservers(); // could be modified
}

int Grid::getHighScore(){
    return this->highScore;
}

bool Grid::getDead(){
    return this->dead;
}

void Grid::setDead(bool alive){
    this->dead = alive;
}

int Grid::getHeight(){
    return this->height;
}

int Grid::getWidth(){
    return this->width;
}

std::vector<std::vector<Cell> >const &Grid::getGrid(){
    return this->mainGrid;
}

void Grid::reset(){
    for (int r=0; r<this->height; ++r){
        for (int c=0; c<this->width; ++c){
            this->mainGrid[r][c].unsetState();
        }
    }

    this->score= 0;
    this->notifyObservers();

    this->setForce(false);
    this->setHeavy(false);
    this->setBlind(false);

    // Level 4 stuff

    delete this->current;
    delete this->next;

    this->lyingBlocks.clear();
}

void Grid::setCurrentLevel(int lev, bool random, string fileName){
    delete this->currentLevel;
    if (lev == 0) this->currentLevel = new ZeroLev(fileName);
	else if (lev == 1) {
	       if (random) this->currentLevel = new OneLev(true);
               else this->currentLevel = new OneLev(false, fileName);
	}
	// else if (lev == 2) {
	// 	if (random) this->currentLevel = new LevelTwo(true);
    //             else this->currentLevel = new LevelTwo(false, fileName);
	// }
	// else if (lev == 3) {
	// 	if (random) this->curLevel = new LevelThree(true);
	// 	else this->curLevel = new LevelThree(false, file);
	// }
	// else if (lev == 4) { 
	// 	if (random) this->curLevel = new LevelFour(true);
	// 	else this->curLevel = new LevelFour(false, file);
	// }
    this->level = 1;
    this->notifyObservers();
}

void Grid::deactivateBlock(){
    for (int r=0; r<4; ++r){
        for (int c=0; c<4; ++c){
            char value = this->current->getBlock()[this->current->getRotate()][r][c];
            int bY = this->current->getY()+r;
            int bX = this->current->getX()+c;

            if (value!='.'){
                this->mainGrid[bY][bX].unsetState();
            }
        }
    }

}

void Grid::findLyingBlock(int lev){
    std::vector<laidBlocks> bloc;
    for (int r=0; r<4; ++r){
        for (int c=0; c<4; ++c){
            if (this->current->getBlock()[this->current->getRotate()][r][c] != '.'){
                bloc.emplace_back(laidBlocks((this->current->getY()+r), lev));
            }
        }
    }
    this->lyingBlocks.emplace_back(bloc);
}


void Grid::activateCell(int x, int y, char state){
    this->mainGrid[x][y].setState(state);
}

void Grid::deactivateCell(int x, int y){
    this->mainGrid[x][y].setState(' '); // shady
}