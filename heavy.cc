#include "heavy.h"

#include "grid.h"

#include <memory>

using namespace std;

Heavy::Heavy(shared_ptr < SpecialAction > SA): Decorator {
  SA
} {}

void Heavy::execute(Grid & gd) {
  SA -> execute(gd);

  if (gd.isHeavy()) {
    // Set the current block to have the special effect heavy
    gd.getCurrentBlock() -> setEffectHeavy(true);
  }
}

Heavy::~Heavy() {}