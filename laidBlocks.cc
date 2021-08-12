#include "laidBlocks.h"

laidBlocks::laidBlocks(int coord, int levelGen) {
  this -> coord = coord;
  this -> levelGen = levelGen;
  this -> Occupied = false;
}

laidBlocks::~laidBlocks() {}

int laidBlocks::getLevelGen() {
  return this -> levelGen;
}

int laidBlocks::getCoord() {
  return this -> coord;
}

bool laidBlocks::getOccupied() {
  return this -> Occupied;
}

void laidBlocks::setCoord(int coord) {
  this -> coord = coord;
}

void laidBlocks::setOccupied(bool op) {
  this -> Occupied = op;
}