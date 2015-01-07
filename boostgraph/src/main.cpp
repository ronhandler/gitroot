#include "main.h"

class Vertex{
public:
    std::string label;
    std::string color;
	Vertex() {}
	Vertex(const std::string l, const std::string c) {label=l; color=c;}
};

class Edge{
public:
    float probability;
	Edge() { probability=0; }
	Edge(float i): probability(i) {}
};

//Some typedefs for simplicity
typedef adjacency_list< listS, vecS, directedS, Vertex, Edge > digraph;
typedef boost::graph_traits<digraph>::vertex_descriptor vertex_t;
typedef boost::graph_traits<digraph>::edge_descriptor edge_t;

int main(int argc, char* argv[])
{

    /* define the graph type
          listS: selects the STL list container to store 
                 the OutEdge list
          vecS: selects the STL vector container to store 
                the vertices
          directedS: selects directed edges
    */
   //typedef adjacency_list< listS, vecS, directedS > digraph;
   // instantiate a digraph object with 8 vertices
   digraph g(8);

   vertex_t u = add_vertex(Vertex("hello", "red"), g);
   vertex_t v = add_vertex(Vertex("world", "blue"), g);

   // add some edges
   add_edge(0, 1, Edge(14), g);
   add_edge(1, 5, g);
   add_edge(5, 6, g);
   add_edge(2, 3, g);
   add_edge(2, 4, g);
   add_edge(3, 5, g);
   add_edge(4, 5, g);
   add_edge(5, 7, g);
   add_edge(7, u, g);
   add_edge(u, v, g);

   // represent graph in DOT format and send to cout
   dynamic_properties dp;
   dp.property("color", get(&Vertex::color, g));
   dp.property("label", get(&Vertex::label, g));
   dp.property("node_id", get(vertex_index, g));
   dp.property("label", get(&Edge::probability, g));
   write_graphviz_dp(cout, g, dp);
   //write_graphviz(cout, g);

   return 0;
}

