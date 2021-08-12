#include <string>

#include <vector>

#include "block.h"

#include "zblock.h"

using namespace std;

zblock::zblock(bool heavy): Block(0, 0, 0, heavy, false) {}

char zblock::whichBlock() {
  return 'Z';
}

// gives the shape of the block
vector < int > zblock::getShape() {
  return {
    0,
    1,
    5,
    6
  };
}

vector < vector < string >> zblock::getBlock() {
  return {
    {
      "....",
      "....",
      "ZZ..",
      ".ZZ."
    },
    {
      "....",
      ".Z..",
      "ZZ..",
      "Z..."
    },
    {
      "....",
      "....",
      "ZZ..",
      ".ZZ."
    },
    {
      "....",
      ".Z..",
      "ZZ..",
      "Z..."
    }
  };
}

zblock::~zblock() {}