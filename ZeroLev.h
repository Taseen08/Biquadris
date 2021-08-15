#ifndef _LEV0_H_
#define _LEV0_H_

#include <string>

#include <iostream>

#include <fstream>

#include "Level.h"

#include "block.h"

class ZeroLev: public Level {
  int selfLevel;
  std::ifstream inputFile; 
  bool random = false;
  std::string source;
  int same;
  public:
    ZeroLev(std::string source);
  void getOldBlocks() override;
  Block * NextBlock(int pos) override;
  int getLevel() override;
  bool randomCheck() override;
  std::string getInputFile() override;
  void setSame(int same) override; 
  void toggleSame() override; 
  
  ~ZeroLev() override;

};
#endif