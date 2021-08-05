#ifndef BLOCK_H
#define BLOCK_H
#include <string>
#include <vector>
using namespace std;

// abstract block class
class Block {

	protected:
		int x; // x-coordinate of top left part of block
        int y; // y-coordinate of top left part of block
        int rotate; // 0 represents default, 1 is 90 degrees clockwise, 2 is 180 degrees clockwise, 3 is 270 degrees clockwise
		bool specialHeavy;
        bool levelHeavy; 
	
	public:
		virtual vector<vector<string>> getBlock() = 0; 
		virtual char whichBlock() = 0; 
		int getX(); 
		int getY(); 
	    int getRotate(); 
		void setX(int x); 
		void setY(int y); 
		void setRotate(int rotate); 
		bool isEffectHeavy(); 
		bool isLevelHeavy(); 
		void setEffectHeavy(bool specialHeavy); 
        virtual vector<int> getShape() = 0;   // gives the shape of the block
		Block(int x, int y, int rotate, bool levelHeavy, bool specialHeavy);
		virtual ~Block();
};

#endif

