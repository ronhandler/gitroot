#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <string>
#include <stddef.h>

class BaseBlock
{
protected:
	static const int BlockDimension = 4; /* Blocks will be 4x4. */
	bool Shape[BlockDimension][BlockDimension];
	virtual void MakeShape() = 0;
public:
	int x, y;
	BaseBlock() {
		// Init the shape to zeros.
		for (int i=0; i<BlockDimension*BlockDimension; ++i)
			Shape[0][i] = 0;
		x=0; y=0;
	}
	virtual ~BaseBlock() {};
	virtual bool inRange(int i, int j) {
		if (i<x || j<y)
			return false;
		if (i>=x+BlockDimension || j>=y+BlockDimension)
			return false;
		return true;
	}
	virtual void print(int i, int j) {
		//std::cout << i << "x" << j << "\n";
		if (BaseBlock::Shape[i][j])
			std::cout << "1 ";
		else
			std::cout << "_ ";
	}
	virtual void func() = 0;
};

class BlockJ: public BaseBlock
{
	// Make the desired block shape.
	virtual void MakeShape() {
		BaseBlock::Shape[1][0]=1; // 0100
		BaseBlock::Shape[1][1]=1; // 0100
		BaseBlock::Shape[0][2]=1; // 1100
		BaseBlock::Shape[1][2]=1; // 0000
	}
public:
	BlockJ() { MakeShape(); }
	virtual void func() {
		std::cout << "I'm a J shape!\n";
	}
};

class BlockL: public BaseBlock
{
	// Make the desired block shape.
	virtual void MakeShape() {
		BaseBlock::Shape[0][0]=1; // 1000
		BaseBlock::Shape[0][1]=1; // 1000
		BaseBlock::Shape[0][2]=1; // 1100
		BaseBlock::Shape[1][2]=1; // 0000
	}
public:
	BlockL() { MakeShape(); }
	virtual void func() {
		std::cout << "I'm an L shape!\n";
	}
};

class Factory
{
public:
	virtual BaseBlock *createBlock(const std::string &type) {
		if(type == "J")
			return new BlockJ;
		if(type == "L")
			return new BlockL;
		if(type == "...")
			; /* ... */
		return NULL;
	}
};

#endif

