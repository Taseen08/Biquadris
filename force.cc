#include "force.h"
#include "grid.h"
#include <memory>

using namespace std;


Force::Force(shared_ptr<SpecialAction> SA, char theBlock) : Decorator{SA}, theBlock{theBlock} {}

void Force::execute(Grid &gd) {
	//Apply the effect to the board
	SA->execute(gd);
	
	if(gd.isForce()) {
		//Match heavy to level
            Operations all_operations;
        	bool heavy = false;
                if (gd.getLevel() == 3 || gd.getLevel() == 4) {
                    heavy = true;
                }

                Block * old = gd.getCurrentBlock();
                Block * newblock = nullptr;
                if (theBlock == 'J') {
                    newblock = new jblock{heavy};
                } else if (theBlock == 'T') {
                    newblock = new tblock{heavy};
                } else if (theBlock == 'O') {
                    newblock = new oblock{heavy};
                } else if (theBlock == 'S') {
                    newblock = new sblock{heavy};
                } else if (theBlock == 'Z') {
                    newblock = new zblock{heavy};
                } else if (theBlock == 'L') {
                    newblock = new lblock{heavy};
                } else if (theBlock == 'I') {
                    newblock = new iblock{heavy};
                } else {
                    return;
                }
            

            newblock->setX(old->getX());
            newblock->setY(old->getY());
            gd.deactivateBlock();
            gd.setCurrentBlock(newblock);

            if (all_operations.isValid(gd,0,0,0)) {
                all_operations.moveBlock(gd,0,0,0);
                delete old;
            } else {
                gd.setCurrentBlock(old);
                all_operations.moveBlock(gd,0,0,0);
                delete newblock;
            }
	}
}
Force::~Force() {}