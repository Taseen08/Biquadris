#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>
#include "observer.h"
//#include "tileinfo.h"
using namespace std;

class Block;
class Cell; 

class TextDisplay: public Observer {
	int h;
    int w;	
	vector<vector<char>> displayOne;
	vector<vector<char>> displayTwo;
	// display preview at bottom
	vector<char> stateOne;
	vector<char> stateTwo;
	Grid *gridOne; 
	Grid *gridTwo; 
	public:
		TextDisplay(int w, int h, Grid *gridOne, Grid *gridTwo);
		void notify(Cell &who) override;
		void notify(Grid &who) override;
		void blind(int player, ostream &out) const;
		void modifyNext(Block* nextBlock, int player);
        void makeReadyNext();
		void showDisplay(ostream &out) const;
		friend ostream &operator<<(ostream &out, const TextDisplay &td);
		~TextDisplay();
};
#endif