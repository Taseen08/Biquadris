#ifndef _LEV4_H_
#define _LEV4_H_

#include "Level.h"

#include "block.h"

#include <iostream>

#include <fstream>

#include <string>

class FourLev: public Level {
  int selfLevel;
  int same; 
  std::ifstream inputFile;
  bool random = true;
  std::string source;
  public:
    FourLev(bool random, std::string source = "");
  void getOldBlocks() override;
  Block * NextBlock(int pos) override;
  int getLevel() override;
  bool randomCheck() override;
  std::string getInputFile() override;
  void setSame(int same) override; 
  void toggleSame() override; 
  ~FourLev() override;
};
#endif