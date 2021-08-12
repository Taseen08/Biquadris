#include <string>

#include <vector>

#include "block.h"

#include "jblock.h"

using namespace std;

jblock::jblock(bool heavy): Block(0, 0, 0, heavy, false) {}

char jblock::whichBlock() {
  return 'J';
}

// gives the shape of the block
vector < int > jblock::getShape() {
  return {
    0,
    4,
    5,
    6
  };
}

vector < vector < string >> jblock::getBlock() {
  return {
    {
      "....",
      "....",
      "J...",
      "JJJ."
    },
    {
      "....",
      "JJ..",
      "J...",
      "J..."
    },
    {
      "....",
      "....",
      "JJJ.",
      "..J."
    },
    {
      "....",
      ".J..",
      ".J..",
      "JJ.."
    }
  };
}

jblock::~jblock() {}