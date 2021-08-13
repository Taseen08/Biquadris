#ifndef _OBSERVER_H_
#define _OBSERVER_H_

class Cell;
class Grid;

class Observer {
  public:
    virtual void notify(Grid & who) = 0;
  virtual void notify(Cell & who) = 0;
  virtual~Observer();
};

#endif