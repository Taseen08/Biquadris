#ifndef JBLOCK_H
#define JBLOCK_H
#include <string>
#include <vector>
#include "block.h"
using namespace std;


class jblock : public Block {
	public:
		jblock(bool heavy);
        char whichBlock() override; 
		vector<vector<string>> getBlock() override; 
		vector<int> getShape() override; 
		~jblock() override;
};

#endif