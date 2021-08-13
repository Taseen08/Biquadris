#ifndef _LEV_H_
#define _LEV_H_

#include "block.h"

#include "jblock.h"

#include "oblock.h"

#include "lblock.h"

#include "iblock.h"

#include "tblock.h"

#include "sblock.h"

#include "zblock.h"

#include <iostream>

#include <fstream>

#include <vector>

class Level {
  std::ifstream inputFile;
  protected:
    std::vector < char > blocks;
  public:
    virtual int getLevel() = 0;
  virtual bool randomCheck() = 0;
  virtual std::string getInputFile() = 0;
  virtual void getOldBlocks() = 0;
  virtual Block * NextBlock(int loc) = 0;
  virtual void setSame(int same) = 0; 
  virtual void toggleSame() = 0;
  virtual~Level();

};

#endif