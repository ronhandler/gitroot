#ifndef BOARD_H
#define BOARD_H

#include <iostream>
using namespace std;
#include <string>
#include <stddef.h>

#include "block.h"

class Board
{
protected:
	const static int Height=22;
	const static int Width=10;
	int arr[Width][Height];
	Factory blockFactory;
	BaseBlock *currblock;
public:
	Board() {
		// Init the board to zeros.
		for (int j=0; j<Height; ++j) {
			for (int i=0; i<Width; ++i) {
				arr[i][j]=0;
			}
		}
	}
	void print() {
		for (int j=0; j<Height; ++j) {
			for (int i=0; i<Width; ++i) {
				if (currblock->inRange(i,j)) {
					currblock->print(i-currblock->x,j-currblock->y);
				} else {
					if (arr[i][j]!=0)
						cout << arr[i][j] << " ";
					else
						cout << "_ ";
				}
			}
			cout << endl;
		}
	}
	void func() {
		currblock = blockFactory.createBlock("L");
		currblock->x=7;
		currblock->y=2;
	}
};

#endif

