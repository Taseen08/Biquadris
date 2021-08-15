#ifndef _LEV2_H_
#define _LEV2_H_

#include "Level.h"

#include "block.h"

#include <iostream>

#include <fstream>

#include <string>

class TwoLev: public Level {
  int selfLevel;
  std::ifstream inputFile;
  bool random = true;
  std::string source;
  int same;
  public:
    TwoLev(bool random, std::string source = "");
  void getOldBlocks() override;
  Block * NextBlock(int pos) override;
  int getLevel() override;
  bool randomCheck() override;
  std::string getInputFile() override;
  void setSame(int same) override; 
  void toggleSame() override; 
  ~TwoLev() override;
};
#endif