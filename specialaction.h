#ifndef SPECIALACTION_H
#define SPECIALACTION_H

class Grid;

class SpecialAction {
  public:
    virtual void execute(Grid & grid) = 0; //execute method for the special actions
  virtual~SpecialAction();
};

#endif