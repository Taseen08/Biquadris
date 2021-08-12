#include <string>

#include <vector>

#include "block.h"

#include "tblock.h"

using namespace std;

tblock::tblock(bool heavy): Block(0, 0, 0, heavy, false) {}

char tblock::whichBlock() {
  return 'T';
}

// gives the shape of the block
vector < int > tblock::getShape() {
  return {
    0,
    1,
    2,
    5
  };
}

vector < vector < string >> tblock::getBlock() {
  return {
    {
      "....",
      "....",
      "TTT.",
      ".T.."
    },
    {
      "....",
      ".T..",
      "TT..",
      ".T.."
    },
    {
      "....",
      "....",
      ".T..",
      "TTT."
    },
    {
      "....",
      "T...",
      "TT..",
      "T..."
    }
  };
}

tblock::~tblock() {}