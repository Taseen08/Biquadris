#ifndef ABLOCK_H
#define ABLOCK_H
#include <string>
#include <vector>
#include "block.h"
using namespace std;

class ablock : public Block {
	public:
		ablock(bool heavy);
        char whichBlock() override; 
		vector<vector<string>> getBlock() override; 
		vector<int> getShape() override; 
		~ablock() override;
};

#endif