#include <string>
#include <vector>
#include "block.h"
#include "oblock.h"
using namespace std;

oblock::oblock(bool heavy) : Block(0, 0, 0, heavy, false) {}

char oblock::whichBlock() { 
    return 'O'; 
}

// gives the shape of the block
vector<int> oblock::getShape() { 
    return {0, 1, 4, 5}; 
}

vector<vector<string>> oblock::getBlock() {
    return {{"....", "....", "OO..", "OO.."},
            {"....", "....", "OO..", "OO.."},
            {"....", "....", "OO..", "OO.."},
            {"....", "....", "OO..", "OO.."}};
}

oblock::~oblock() {}