#include <time.h>

#include <iostream>

#include <stdlib.h>

#include <string>

#include <vector>

#include "ThreeLev.h"

#include "block.h"

ThreeLev::ThreeLev(bool random, std::string source) {
  this -> selfLevel = 3;
  this -> random = random;
  this -> source = source;
}

void ThreeLev::getOldBlocks() {
  if (this -> random) {
    return;
  }
  char s;
  this -> inputFile.open(this -> source);
  while (this -> inputFile >> s) {
    this -> blocks.emplace_back(s);
  }
}

Block * ThreeLev::NextBlock(int loc) {
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
  if (this -> blocks[k] == 'I') return new iblock {
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

int ThreeLev::getLevel() {
  return this -> selfLevel;
}

bool ThreeLev::randomCheck() {
  return this -> random;
}

std::string ThreeLev::getInputFile() {
  return this -> source;
}

ThreeLev::~ThreeLev() {}