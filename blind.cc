#include "blind.h"
#include "grid.h"
#include <memory>
using namespace std;


Blind::Blind(shared_ptr<SpecialAction> SA) : Decorator{SA} {}

void Blind::execute(Grid &gd) {
	SA->execute(gd);
}

Blind::~Blind() {}