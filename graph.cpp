#include "graph.h"
#include <iostream>
using std::cout;
namespace hbutds{

    auto generate_test_graph() -> Graph<char>{
        Graph<char> graph;
        graph.add_vertex('a');
        graph.add_vertex('b');
        graph.add_vertex('c');
        graph.add_vertex('d');
        graph.add_vertex('e');
        graph.add_vertex('f');

        graph.add_edge('a', 'b', 3);
        graph.add_edge('b', 'a', 3);

        graph.add_edge('a', 'e', 1);
        graph.add_edge('e', 'a', 1);

        graph.add_edge('b', 'c', 7);
        graph.add_edge('c', 'b', 7);

        graph.add_edge('b', 'd', 1);
        graph.add_edge('d', 'b', 1);

        graph.add_edge('b', 'e', 1);
        graph.add_edge('e', 'b', 1);

        graph.add_edge('c', 'd', 4);
        graph.add_edge('d', 'c', 4);

        graph.add_edge('d', 'e', 3);
        graph.add_edge('e', 'd', 3);

        graph.add_edge('f', 'e', 5);
        graph.add_edge('e', 'f', 5);

        return graph;
    }

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

    void test_get_vertex(){
        Graph<char> graph;
        auto a_id {graph.add_vertex('a')};
        auto b_id {graph.add_vertex('b')};
        auto c_id {graph.add_vertex('c')};
        graph.add_edge('a', 'b', 2);
        graph.add_edge('a', 'c', 1);
        graph.add_edge('b', 'c', 3);

        assert(graph.get_vertex(0) == 'a');
        assert(graph.get_vertex(2) == 'c');
        cout<<"@ Graph::get_vertex works\n";
    }

    void graph_works(){
        test_add_vertex();
        test_add_edge();
        test_remove_edge();
        test_remove_vertex();
        test_get_vertex();
        cout<<"hbutds::Graph works!\n";
    }
}