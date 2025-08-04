#include "graph.h"
#include <iostream>
using std::cout;
namespace hbutds{

    void test_add_vertex(){
        Graph<char> graph;
        graph.add_vertex('a');
        graph.add_vertex('b');
        assert(graph.get_vertex_id('a').value() == 0);
        assert(graph.get_vertex_id('b').value() == 1);
        assert(graph.vertex_size() == 2);
        cout<<"@ graph::add_vertex works\n";
    }

    void test_add_edge(){
        Graph<char> graph;
        graph.add_vertex('a');
        graph.add_vertex('b');
        graph.add_edge('a', 'b', 2);
        assert(graph.get_edge_cost('a', 'b') == 2);
        assert(graph.get_edge_cost('b', 'a') 
            == std::numeric_limits<double>::infinity());
        assert(graph.edge_size() == 1);
        cout<<"@ graph::add_edge works\n";
    }
    void graph_works(){
        test_add_vertex();
        test_add_edge();
        cout<<"hbutds::Graph works!\n";
    }
}