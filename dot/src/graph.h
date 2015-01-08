#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
using namespace std;
#include <map>

typedef unsigned long int vertex_index;

class Edge
{
public:
	// Edge from v->u.
	vertex_index v;
	vertex_index u;
    float weight;
	Edge() { weight=0; v=0; u=0; }
	Edge(vertex_index V, vertex_index U): v(V), u(U) {}
	Edge(float i): weight(i) {}
	void print()
	{
		cout << "\t" << v << " -> " << u << ";" <<  endl; 
	}
};

class Vertex
{
public:
	int x;
	int y;
	vertex_index index;
	Vertex(): x(0), y(0), index(0) { }
	Vertex(vertex_index i): x(0), y(0) { index=i; }
	Vertex(double x, double y) {
		this->x=x;
		this->y=y;
	}
	void print()
	{
		cout << "\t" << index << ";" << endl;
	}
};

class Graph
{
public:
	void print_dot_format()
	{
		cout << "digraph MyGraph {" << endl;
		map< vertex_index, Vertex >::iterator it; 
		for (it = vertex_map.begin(); it != vertex_map.end(); ++it) {
			it->second.print();
		}

		for (it = vertex_map.begin(); it != vertex_map.end(); ++it) {
			map< vertex_index, Edge >::iterator eit;
			for (eit = (edge_map[it->second.index]).begin(); eit != (edge_map[it->second.index]).end(); ++eit) {
				eit->second.print();
			}
		}
		cout << "}" << endl;
	}
	void add_edge(vertex_index v, vertex_index u)
	{
		// If v does not exist, we should create it.
		if (vertex_map.find(v) == vertex_map.end()) {
			vertex_map[v] = Vertex(v);
		}
		if (vertex_map.find(u) == vertex_map.end()) {
			vertex_map[u] = Vertex(u);
		}
		(edge_map[v])[u] = Edge(v,u);
	}
private:
	static vertex_index vertices_number;
	map< vertex_index, Vertex > vertex_map;
	map< vertex_index, map< vertex_index, Edge > > edge_map;
};

#endif

