#ifndef IBLOCK_H
#define IBLOCK_H

#include <string>

#include <vector>

#include "block.h"

using namespace std;

class iblock: public Block {
  public: iblock(bool heavy);
  char whichBlock() override;
  vector < vector < string > > getBlock() override;
  vector < int > getShape() override;~iblock() override;
};

#endif