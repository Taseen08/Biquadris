#include <string>

#include <vector>

#include "block.h"

#include "sblock.h"

using namespace std;

sblock::sblock(bool heavy): Block(0, 0, 0, heavy, false) {}

char sblock::whichBlock() {
  return 'S';
}

// gives the shape of the block
vector < int > sblock::getShape() {
  return {
    1,
    2,
    4,
    5
  };
}

vector < vector < string >> sblock::getBlock() {
  return {
    {
      "....",
      "....",
      ".SS.",
      "SS.."
    },
    {
      "....",
      "S...",
      "SS..",
      ".S.."
    },
    {
      "....",
      "....",
      ".SS.",
      "SS.."
    },
    {
      "....",
      "S...",
      "SS..",
      ".S.."
    }
  };
}

sblock::~sblock() {}