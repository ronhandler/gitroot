#include "main.h"

int main(int argc, char* argv[])
{
	Graph graph;

	// Add some edges.
	graph.add_edge(1, 2);
	graph.add_edge(2, 6);
	graph.add_edge(6, 7);
	graph.add_edge(3, 4);
	graph.add_edge(3, 5);
	graph.add_edge(4, 6);
	graph.add_edge(5, 6);
	graph.add_edge(6, 8);

	graph.print_dot_format();
	return 0;
}

