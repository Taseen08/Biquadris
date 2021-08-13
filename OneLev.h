#ifndef _LEV1_H_
#define _LEV1_H_

#include "Level.h"

#include "block.h"

#include <string>

#include <iostream>

#include <fstream>

class OneLev: public Level {
  int selfLevel;
  std::ifstream inputFile; //file that this level could potentially use
  bool random = true;
  std::string source;
  int same;
  public:
    OneLev(bool random, std::string source = "");
  void getOldBlocks() override;
  Block * NextBlock(int pos) override;
  int getLevel() override;
  bool randomCheck() override;
  std::string getInputFile() override;
  void setSame(int same) override; // setStreak
  void toggleSame() override; // IncreaseStreak
  ~OneLev() override;
};

#endif