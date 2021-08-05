#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include "observer.h"
//#include "tileinfo.h"

class Subject {
	protected:
		std::vector<Observer *> observers;
	public:
		void attach(Observer *ob);
        void detach(Observer *ob);
		void virtual notifyObservers() = 0;
};

#endif