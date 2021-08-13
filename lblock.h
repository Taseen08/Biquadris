#ifndef LBLOCK_H
#define LBLOCK_H

#include <string>

#include <vector>

#include "block.h"

using namespace std;

class lblock: public Block {
  public: lblock(bool heavy);
  char whichBlock() override;
  vector < vector < string >> getBlock() override;
  vector < int > getShape() override;~lblock() override;
};

#endif