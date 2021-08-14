#ifndef _DECORATOR_H_
#define _DECORATOR_H_

#include "specialaction.h"

#include <memory>

class Decorator: public SpecialAction {
  protected: std::shared_ptr < SpecialAction > SA;
  public: Decorator(std::shared_ptr < SpecialAction > SA);
  void execute(Grid & gd) override;
  virtual~Decorator();
};

#endif