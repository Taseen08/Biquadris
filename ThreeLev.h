#ifndef _LEV3_H_
#define _LEV3_H_
#include "Level.h"
#include "block.h"
#include <iostream>
#include <fstream>
#include <string>

class ThreeLev : public Level {
        int selfLevel;
        std::ifstream inputFile;
        bool random = true; 
        std::string source;
    public:
        ThreeLev(bool random, std::string source = "");
		void getOldBlocks() override;
        Block* NextBlock(int pos) override;
		int getLevel() override;
		bool randomCheck() override;
        std::string getInputFile() override;
        ~ThreeLev() override;
};
#endif