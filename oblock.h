#ifndef OBLOCK_H
#define OBLOCK_H

#include <string>

#include <vector>

#include "block.h"

using namespace std;

class oblock: public Block {
  public: oblock(bool heavy);
  char whichBlock() override;
  vector < vector < string >> getBlock() override;
  vector < int > getShape() override;~oblock() override;
};

#endif