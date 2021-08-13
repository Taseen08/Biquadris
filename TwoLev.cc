#include <time.h>

#include <iostream>

#include <string>

#include <vector>

#include <stdlib.h>

#include "TwoLev.h"

#include "block.h"


TwoLev::TwoLev(bool random, std::string source) {
  this -> selfLevel = 2;
  this -> random = random;
  this -> source = source;
}

void TwoLev::getOldBlocks() {
  if (this -> randomCheck == true) {
    return;
  }

  char s;
  this -> inputFile.open(this -> source);
  while (this -> inputFile >> s) {
    this -> blocks.emplace_back(s);
  }

}

Block * TwoLev::NextBlock(int loc) {
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
      'J',
      'L',
      'O',
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

int TwoLev::getLevel() {
  return this -> selfLevel;
}

bool TwoLev::randomCheck() {
  return false;
}

std::string TwoLev::getInputFile() {
  return this -> source;
}

TwoLev::~TwoLev() {}