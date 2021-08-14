#ifndef LAIDBLOCK_H
#define LAIDBLOCK_H

class laidBlocks {
  int coord; // y-coodinate
  int levelGen; // level for this block
  bool Occupied; // if cleared boolean
  public:
    laidBlocks(int coord, int levelGen);
  ~laidBlocks();
  int getCoord();
  int getLevelGen(); 
  bool getOccupied(); 
  void setCoord(int coord); 
  void setOccupied(bool op); 
};
#endif