#include <vector>

#include <string>

#include "block.h"

using namespace std;

Block::Block(int x, int y, int rotate, bool levelHeavy, bool specialHeavy):
  x {
    x
  }, y {
    y
  }, rotate {
    rotate
  }, levelHeavy {
    levelHeavy
  }, specialHeavy {
    specialHeavy
  } {}

int Block::getX() {
  return x;
}

int Block::getY() {
  return y;
}

int Block::getRotate() {
  return rotate;
}

void Block::setX(int new_x) {
  x = new_x;
}

void Block::setY(int new_y) {
  y = new_y;
}

void Block::setRotate(int new_rotate) {
  rotate = new_rotate;
}

bool Block::isEffectHeavy() {
  return specialHeavy;
}

void Block::setEffectHeavy(bool specialHeavy) {
  this -> specialHeavy = specialHeavy;
}

bool Block::isLevelHeavy() {
  return levelHeavy;
}

Block::~Block() {}