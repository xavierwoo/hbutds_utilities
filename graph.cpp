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

    void test_remove_edge(){
        Graph<char> graph;
        graph.add_vertex('a');
        graph.add_vertex('b');
        graph.add_vertex('c');
        graph.add_edge('a', 'b', 2);
        graph.add_edge('a', 'c', 1);

        graph.remove_edge('a', 'b');

        assert(graph.edge_size() == 1);
        assert(graph.get_edge_cost('a', 'b')
            == std::numeric_limits<double>::infinity());
        assert(graph.get_edge_cost('a', 'c') == 1);
        cout<<"@ graph::remove_edge works\n";
    }

    void test_remove_vertex(){
        Graph<char> graph;
        auto a_id {graph.add_vertex('a')};
        auto b_id {graph.add_vertex('b')};
        auto c_id {graph.add_vertex('c')};
        graph.add_edge('a', 'b', 2);
        graph.add_edge('a', 'c', 1);
        graph.add_edge('b', 'c', 3);

        graph.remove_vertex('b');

        assert(graph.vertex_size() == 2);
        assert(graph.edge_size() == 1);
        assert(graph.get_edge_cost_by_id(a_id, b_id) == std::numeric_limits<double>::infinity());
        assert(graph.get_edge_cost_by_id(b_id, c_id) == std::numeric_limits<double>::infinity());
        assert(graph.get_edge_cost_by_id(a_id, c_id) == 1);
        cout<<"@ Graph::remove_vertex works\n";
    }

    void graph_works(){
        test_add_vertex();
        test_add_edge();
        test_remove_edge();
        test_remove_vertex();

        cout<<"hbutds::Graph works!\n";
    }
}