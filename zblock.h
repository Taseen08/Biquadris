#ifndef ZBLOCK_H
#define ZBLOCK_H
#include <string>
#include <vector>
#include "block.h"
using namespace std;


class zblock : public Block {
	public:
		zblock(bool heavy);
        char whichBlock() override; 
		vector<vector<string>> getBlock() override; 
		vector<int> getShape() override; 
		~zblock() override;
};

#endif