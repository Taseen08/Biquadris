#include <iostream>

#include <string>

#include <stdlib.h>

#include <time.h>

#include <vector>

#include <fstream>

#include "block.h"

#include "OneLev.h"

OneLev::OneLev(bool random, std::string source) {
  this -> random = random;
  this -> source = source;
  this -> selfLevel = 1;
  this->same = 0;
}

void OneLev::getOldBlocks() {
  if (this -> random) {
    return;
  }
  char s;
  this -> inputFile.open(this -> source);
  while (this -> inputFile >> s) {
    this -> blocks.emplace_back(s);
  }
}

Block * OneLev::NextBlock(int loc) {
  int k;
  if (this -> random == false) {
    this -> getOldBlocks();
    k = loc % this -> blocks.size();
  } else {
    this -> blocks.clear();
    this -> blocks = {
      'S',
      'Z',
      'I',
      'I',
      'J',
      'J',
      'L',
      'L',
      'O',
      'O',
      'T',
      'T'
    };
    k = rand() % (this -> blocks.size());
  }
  if (this -> blocks[k] == 'I') return new iblock {
    false
  };
  else if (this -> blocks[k] == 'J') return new jblock {
    false
  };
  else if (this -> blocks[k] == 'L') return new lblock {
    false
  };
  else if (this -> blocks[k] == 'O') return new oblock {
    false
  };
  else if (this -> blocks[k] == 'S') return new sblock {
    false
  };
  else if (this -> blocks[k] == 'Z') return new zblock {
    false
  };
  else return new tblock {
    false
  };

}

int OneLev::getLevel() {
  return this -> selfLevel;
}

bool OneLev::randomCheck() {
  return false;
}

std::string OneLev::getInputFile() {
  return this -> source;
}

void OneLev::toggleSame() {
  this->same += 1;
}
void OneLev::setSame(int same) {
  this->same = same;
}


OneLev::~OneLev() {}