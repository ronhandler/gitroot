#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
using namespace std;
#include <algorithm>    // std::find
#include <list>
#include <map>

class Pos {
public:
	double x,y;
	Pos(double i=0, double j=0) {x=i; y=j;}
};

class Node
{
public:
	Node() { }
	Node(int i, Pos p=(Pos(0,0)), double w=0) { index=i; weight=w; pos=p; }
	int index;
	Pos pos;
	double weight;
	std::list< Node * > edges;
	void print() {
		std::list<Node * >::iterator iter;
		for (iter = edges.begin(); iter!=edges.end(); ++iter) {
			Node *n = *iter;
			std::cout << "  Edge: " << index << " <--> " << n->index << std::endl;
		}
	}
};

class Graph
{
public:
	std::map< int, Node > nodes;
	void add(Node x, Node y, double w=1) {
		if (x.index == y.index)	{
			// No need to create an edge between one node and itself.
			return;
		}
		std::map< int, Node >::iterator it;
		it = nodes.find(x.index);
		if (it == nodes.end()) { // Not found.
			// Create a node.
			nodes.insert ( std::pair< int, Node > (x.index, x) );
		}
		it = nodes.find(y.index);
		if (it == nodes.end()) { // Not found.
			// Create a node.
			nodes.insert ( std::pair< int, Node > (y.index, y) );
		}

		it = nodes.find(x.index);
		Node *a = &(it->second);
		it = nodes.find(y.index);
		Node *b = &(it->second);

		std::list<Node * >::iterator iter;
		
		iter = std::find (b->edges.begin(), b->edges.end(), a);
		if (iter == b->edges.end() ) { // Not found.
			// Add the edge to the list of edges.
			b->edges.push_back(a);
		}
		iter = std::find (a->edges.begin(), a->edges.end(), b);
		if (iter == a->edges.end() ) { // Not found.
			// Add the edge to the list of a->edges.
			a->edges.push_back(b);
		}

	}
	void print() {
		std::map< int, Node >::iterator it;
		it = nodes.begin();
		for (it = nodes.begin(); it!=nodes.end(); it++) {
			cout << "Node: " << it->second.index << "\n";
			it->second.print();
		}
	}
};


#endif

