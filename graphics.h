#ifndef GRAPHICS_H_
#define GRAPHICS_H_
#include "subject.h"
#include "observer.h"
#include "window.h"
#include <string>

using namespace std;

class GraphicsDisplay : public Observer {
	size_t tw; //represents the width of a single tile
	size_t dw; //width of the entire window
	size_t dh; //height of the entire window
	size_t bw; //width of the board
        size_t bh; //height of the board
	Xwindow xw;
	Grid *b1; //pointer to Player One's board
        Grid *b2; //pointer to Player Two's board
	size_t p1borderL; //distance from left for p1's board
	size_t p2borderL; //distance from left for p2's board
	size_t borderT; 
	size_t space; //represents the space between the two boards
	public:
		GraphicsDisplay(size_t tw, size_t dw, size_t dh, size_t bw, size_t bh, Grid *b1, Grid *b2);
		~GraphicsDisplay();
		void init();
		void notify(Cell &whoNotified) override;
                void notify(Grid &whoNotified) override;
		void applyBlind(size_t player);
		void removeBlind(Grid *b);
		void displayWinner(size_t player);
};

#endif