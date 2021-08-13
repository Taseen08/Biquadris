#include "ZeroLev.h"

#include "block.h"

#include <iostream>

#include <fstream>

#include <string>

ZeroLev::ZeroLev(std::string source) {
  this -> selfLevel = 0;
  this -> source = source;
  this->same = 0;
}

Block * ZeroLev::NextBlock(int loc) {
  this -> getOldBlocks();
  int j = loc % (this -> blocks.size());
  if (this -> blocks[j] == 'I') return new iblock {
    false
  };
  else if (this -> blocks[j] == 'J') return new jblock {
    false
  };
  else if (this -> blocks[j] == 'L') return new lblock {
    false
  };
  else if (this -> blocks[j] == 'O') return new oblock {
    false
  };
  else if (this -> blocks[j] == 'S') return new sblock {
    false
  };
  else if (this -> blocks[j] == 'Z') return new zblock {
    false
  };
  else return new tblock {
    false
  };
}

void ZeroLev::getOldBlocks() {
  char state;
  this -> inputFile.open(source);
  while (this -> inputFile >> state) {
    this -> blocks.emplace_back(state);
  }

}

int ZeroLev::getLevel() {
  return this -> selfLevel;
}

std::string ZeroLev::getInputFile() {
  return this -> source;
}

bool ZeroLev::randomCheck() {
  return false;
}

void ZeroLev::toggleSame() {
  this->same += 1;
}
void ZeroLev::setSame(int same) {
  this->same = same;
}

ZeroLev::~ZeroLev() {}