#ifndef _LEV4_H_
#define _LEV4_H_
#include "Level.h"
#include "block.h"
#include <iostream>
#include <fstream>
#include <string>

class FourLev : public Level {
        int selfLevel;
        int same; // streak
        std::ifstream inputFile;
        bool random = true; 
        std::string source;
    public:
        FourLev(bool random, std::string source = "");
		void getOldBlocks() override;
        Block* NextBlock(int pos) override;
		int getLevel() override;
        void setSame(int same); // setStreak
        void toggleSame(); // IncreaseStreak
		bool randomCheck() override;
        std::string getInputFile() override;
        ~FourLev() override;
};
#endif