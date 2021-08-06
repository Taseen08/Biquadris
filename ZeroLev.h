#ifndef _LEV0_H_
#define _LEV0_H_
#include <string>
#include <iostream>
#include <fstream>
#include "Level.h"
#include "block.h"

class ZeroLev: public Level{
    int selfLevel;
    std::ifstream inputFile; //file that this level could potentially use
    bool random = false; 
    std::string source;

    public:
    ZeroLev(std::string source);
	void getOldBlocks() override;
    Block* NextBlock(int pos) override;
    int getLevel() override;
    bool randomCheck() override;
    std::string getInputFile() override;
    ~ZeroLev() override;

};
#endif