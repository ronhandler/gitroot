#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

static const int inf = std::numeric_limits<int>::max();

class Node {
public:
	int Value;
	Node *parent;
	Node(): Value(inf), parent(NULL) { }
};

class Road {
private:
public:
	static const int N=20;
	static const int G=6;
	Node array[N][G];
	vector<int> d;	// Distances.
	vector<int> p;	// Prices.
	Road();	// Constructor.
	void Solve();
	void printSolution();
};

#endif

