#ifndef SBLOCK_H
#define SBLOCK_H
#include <string>
#include <vector>
#include "block.h"
using namespace std;

class sblock : public Block {
	public:
		sblock(bool heavy);
        char whichBlock() override; 
		vector<vector<string>> getBlock() override; 
		vector<int> getShape() override; 
		~sblock() override;
};

#endif