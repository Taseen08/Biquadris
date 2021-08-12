#include <time.h>

#include <iostream>

#include <stdlib.h>

#include <string>

#include <vector>

#include "FourLev.h"

#include "block.h"

FourLev::FourLev(bool random, std::string source) {
  this -> selfLevel = 4;
  this -> random = random;
  this -> source = source;
  this -> same = 0;
  this -> blocks.clear();
}

void FourLev::getOldBlocks() {
  if (this -> random) {
    return;
  }
  char s;
  this -> inputFile.open(this -> source);
  while (this -> inputFile >> s) {
    this -> blocks.emplace_back(s);
  }
}

Block * FourLev::NextBlock(int loc) {
  int k;
  if (this -> random == false) {
    this -> getOldBlocks();
    k = loc % this -> blocks.size();
  } else {
    this -> blocks.clear();
    this -> blocks = {
      'S',
      'S',
      'Z',
      'Z',
      'I',
      'J',
      'L',
      'O',
      'T'
    };
    k = rand() % (this -> blocks.size());
  }
  if ((this -> same > 0) && (this -> same % 5 == 0)) return new xblock();
  else if (this -> blocks[k] == 'I') return new iblock {
    true
  };
  else if (this -> blocks[k] == 'J') return new jblock {
    true
  };
  else if (this -> blocks[k] == 'L') return new lblock {
    true
  };
  else if (this -> blocks[k] == 'O') return new oblock {
    true
  };
  else if (this -> blocks[k] == 'S') return new sblock {
    true
  };
  else if (this -> blocks[k] == 'Z') return new zblock {
    true
  };
  else return new tblock {
    true
  };
}

int FourLev::getLevel() {
  return this -> selfLevel;
}

bool FourLev::randomCheck() {
  return this -> random;
}

std::string FourLev::getInputFile() {
  return this -> source;
}

void FourLev::toggleSame() {
  this -> same += 1;
}
void FourLev::setSame(int same) {
  this -> same = same;
}

FourLev::~FourLev() {}