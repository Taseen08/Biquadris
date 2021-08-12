#ifndef _FORCE_H_
#define _FORCE_H_

#include "specialaction.h"

#include "decorator.h"

#include <memory>

using namespace std;

class Force: public Decorator {
  // the block that will be forced
  char theBlock;
  public:
    Force(shared_ptr < SpecialAction > SA, char theBlock);
  void execute(Grid & gd) override;
  ~Force();
};

#endif