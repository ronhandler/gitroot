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

	graph.mod_vertex_property(1, "label", "bahh");
	graph.mod_vertex_property(1, "color", "black");
	graph.mod_vertex_property(1, "fillcolor", "red");
	graph.mod_vertex_property(1, "style", "filled");
	graph.mod_vertex_property(1, "shape", "circle");
	graph.print_dot_format();
	return 0;
}

