#include <iostream>
#include "random.h"

int main(int argc, char* argv[])
{
	// Print a message...
	std::cout << "hello world" << std::endl;

	// Set a random seed.
	Rand::getInstance().seed(500);

	for (int i=0; i<10; ++i) {
		Dice d;
		std::cout << "Rolled: " << d.get1() << ", " << d.get2() << ".\n";
	}
	return 0;
}

