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
#include "specialaction.h"
#include "Operations.h"
#include "specialaction.h"

class TextDisplay;
class laidBlocks;
class Operations;

class Grid: public Subject, public SpecialAction {
  int height;
  int width;
  int score;
  int highScore;
  int level;
  int player;
  bool heavy;
  bool force;
  bool blind;
  std::vector < std::vector < Cell > > mainGrid;
  std::vector < std::vector < laidBlocks > > lyingBlocks;
  Block * next;
  Block * current;
  Level * currentLevel;
  bool dead;
  bool effect;

  public:
    Grid(int width, int height, int level, int player);
  void init();
  int getWidth();
  int getHeight();
  bool fixedNext = false;
  bool pointsModified = false;
  bool levelModified = false;
  bool hiScoreModified = false;
  bool blindOn = false; 
  bool blindOff = false;
  void setFixedNext(bool booleanVal);
  void setPointsModified(bool booleanVal);
  void setLevelModified(bool booleanVal);
  void setHiScoreModified(bool booleanVal);
  void setObserver(Observer * ob);
  void notifyObservers() override;
  void activateCell(int x, int y, char state); 
  void deactivateCell(int x, int y); 
  void findLyingBlock(int lev); 
  void setBlindOn(bool booleanVal); 
  void setBlindOff(bool booleanVal);
  int getScore() const;
  void reset();
  void setCurrentBlock(Block * currentBlock);
  void setNextBlock(Block * nextBlock);
  Block * getCurrentBlock();
  Block * getNextBlock();
  Level * getCurrentLevel();
  int getLevel();
  void deactivateBlock(); 
  void setCurrentLevel(int level, bool random, string file = "");
  int getPlayer();
  bool isBlind() const;
  void setBlind(bool blind);
  bool isHeavy() const;
  void setHeavy(bool heavy);
  bool isForce() const; 
  void setForce(bool force); 
  bool isEffect() const; 
  void setEffect(bool effectNeeded); 
  int getHighScore();
  void setHighScore(int highScore);
  void setDead(bool dead); 
  bool getDead(); // returns if player is dead
  void execute(Grid &grid) override;
  const std::vector < std::vector < Cell > > & getGrid();
  friend class Operations;
  friend ostream & operator << (ostream & out,
    const Grid & grid);
  ~Grid();

};

#endif