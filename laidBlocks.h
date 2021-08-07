#ifndef LAIDBLOCK_H
#define LAIDBLOCK_H

class laidBlocks{
    int coord; //Y coodinate of part
	int levelGen; //the level the block was generated
	bool Occupied; //Whether the part is cleared;
	public:
		laidBlocks(int coord, int levelGen);
		~laidBlocks();
		int getCoord(); //Returns the y coordinate of the part
		int getLevelGen(); //Returns the level it was generated
		bool getOccupied(); //Returns whether the part was cleared from the board
		void setCoord(int coord); //Sets the Y coordinate of the part
		void setOccupied(bool op); //Sets the cleared boolean
};
#endif