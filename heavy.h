#ifndef _HEAVY_H_
#define _HEAVY_H_
#include "specialaction.h"
#include "decorator.h"
#include <memory>
using namespace std;

class Heavy: public Decorator {
	public:
		Heavy(shared_ptr<SpecialAction> SA);
		void execute(Grid &gd) override;
		~Heavy();
};

#endif