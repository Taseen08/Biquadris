#ifndef SPECIALACTION_H
#define SPECIALACTION_H

class Grid;

class SpecialAction {
  public:
    virtual void execute(Grid & grid) = 0; //execute the method for different special actions
  virtual~SpecialAction();
};

#endif