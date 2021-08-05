#include <string>
#include <vector>
#include "block.h"
#include "iblock.h"
using namespace std;

iblock::iblock(bool heavy) : Block(0, 0, 0, heavy, false) {}

char iblock::whichBlock() { 
    return 'I'; 
}

// gives the shape of the block
vector<int> iblock::getShape() { 
    return {4, 5, 6, 7}; 
}

vector<vector<string>> iblock::getBlock() {
    return {{"....", "....", "....", "IIII"},
            {"I...", "I...", "I...", "I..."},
            {"....", "....", "....", "IIII"},
            {"I...", "I...", "I...", "I..."}};
}

iblock::~iblock() {}