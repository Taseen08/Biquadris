#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "grid.h"

class Operations {
  public:
    bool isValid(Grid & theGrid, int x, int y, int rotation);
  void moveBlock(Grid & theGrid, int x, int y, int rotation);
  void removeLines(Grid & theGrid);
};

#endif