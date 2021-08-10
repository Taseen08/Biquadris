#ifndef _DECORATOR_H_
#define _DECORATOR_H_
#include "specialaction.h"
#include <memory>

//Decorator class that has a pointer to the abstract special action class
class Decorator: public SpecialAction {
        protected:
		std::shared_ptr<SpecialAction> SA;
        public:
                Decorator(std::shared_ptr<SpecialAction> SA);
                void execute(Grid &gd) override;
                virtual ~Decorator();
};

#endif