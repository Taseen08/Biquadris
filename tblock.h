#ifndef TBLOCK_H
#define TBLOCK_H
#include <string>
#include <vector>
#include "block.h"
using namespace std;


class tblock : public Block {
	public:
		tblock(bool heavy);
        char whichBlock() override; 
		vector<vector<string>> getBlock() override; 
		vector<int> getShape() override; 
		~tblock() override;
};

#endif