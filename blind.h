#ifndef _BLIND_H_
#define _BLIND_H_

#include "specialaction.h"

#include "decorator.h"

#include <memory>

using namespace std;

class Blind: public Decorator {
  public: Blind(shared_ptr < SpecialAction > SA);
  void execute(Grid & gd) override;~Blind();
};

#endif