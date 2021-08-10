#include "Level.h"
#include "decorator.h"
#include <memory>

Decorator::Decorator(shared_ptr<SpecialAction> SA) : SA{SA} {}

void Decorator::execute(Grid &gd) {
        SA->execute(gd);
}

Decorator::~Decorator() {}