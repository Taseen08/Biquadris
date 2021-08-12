#include <string>

#include <vector>

#include "block.h"

#include "ablock.h"

using namespace std;

ablock::ablock(bool heavy): Block(0, 0, 0, heavy, false) {}

char ablock::whichBlock() {
  return '*';
}

// gives the shape of the block
vector < int > ablock::getShape() {
  return {
    0,
    0,
    0,
    0
  };
}

vector < vector < string >> ablock::getBlock() {
  return {
    {
      "....",
      "....",
      "....",
      "*..."
    },
    {
      "....",
      "....",
      "....",
      "*..."
    },
    {
      "....",
      "....",
      "....",
      "*..."
    },
    {
      "....",
      "....",
      "....",
      "*..."
    }
  };
}

ablock::~ablock() {}