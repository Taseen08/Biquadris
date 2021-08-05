#include <string>
#include <vector>
#include "block.h"
#include "lblock.h"
using namespace std;

lblock::lblock(bool heavy) : Block(0, 0, 0, heavy, false) {}

char lblock::whichBlock() { 
    return 'L'; 
}

// gives the shape of the block
vector<int> lblock::getShape() { 
    return {2, 4, 5, 6}; 
}

vector<vector<string>> lblock::getBlock() {
    return {{"....", "....", "..L.", "LLL."},
            {"....", "L...", "L...", "LL.."},
            {"....", "....", "LLL.", "L..."},
            {"....", "LL..", ".L..", ".L.."}};
}

lblock::~lblock() {}