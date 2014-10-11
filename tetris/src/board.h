#ifndef BOARD_H
#define BOARD_H

#include "block.h"

class Board
{
public:
	// Magic numbers. These set the size of the board.
	const static int HEIGHT=22;
	const static int WIDTH=10;
	const static int OUTOFRANGE=-1;
	Board() {
		init();
	}
	bool set(int x, int y, int value) {
		if (x<0 || x>=WIDTH || y<0 || y>=HEIGHT)
			return false;
		grid[x][y] = value;
		return true;
	}
	int get(int x, int y) const {
		if (x<0 || x>=WIDTH || y<0 || y>=HEIGHT)
			return OUTOFRANGE;
		else
			return grid[x][y];
	}
private:
	void init(void ) {
		// Init the board's grid.
		for (int y=0; y<HEIGHT; ++y) {
			for (int x=0; x<WIDTH; ++x) {
				grid[x][y]=0;
			}
		}
	}
	int grid[WIDTH][HEIGHT];
};

#endif

