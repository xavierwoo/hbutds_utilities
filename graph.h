#ifndef HBUTDS_GRAPH_H
#define HBUTDS_GRAPH_H

#include "vector.h"
#include <optional>
#include <cassert>
#include <limits>
#include <iostream>
#include <format>

using std::cout, std::format;

namespace hbutds{
    
    template <typename T>
    struct Graph{
    private:
        struct ToEdge;
        vector<std::optional<T>> _vertices; // 顶点表
        vector<vector<ToEdge>> _adjacency_list; //邻接表

        unsigned int _vertex_size{0}; //顶点个数
        unsigned int _edge_size{0}; // 边个数
        
    public:

        auto vertex_size() {return _vertex_size;}
        auto edge_size() {return _edge_size;}

        //获取顶点编号
        auto get_vertex_id(const T&) const -> std::optional<unsigned int>;

        //添加顶点
        auto add_vertex(const T&) -> unsigned int;

        //添加变
        void add_edge(const T&, const T&, const double);

        //获取边权值
        auto get_edge_cost(const T&, const T&) const -> double;

        //使用顶点id获得边权值
        auto get_edge_cost_by_id(
                const unsigned int, const unsigned int) const -> double;

        //删除边
        void remove_edge(const T&, const T&);

        //删除顶点
        void remove_vertex(const T&);


        /*图的遍历算法*/
        // 深度优先递归算法
        void dfs_print_recursive(const T&) const;
        void dfs_print_recur(const unsigned int, vector<bool>&) const;
    }; 

    template <typename T>
    struct Graph<T>::ToEdge{
        unsigned int to;
        double cost;
    };

    void graph_works();
    auto generate_test_graph() -> Graph<char>;
}


template <typename T>
auto hbutds::Graph<T>::get_vertex_id(
        const T& vertex
) const -> std::optional<unsigned int>{
    for(auto i=0; i<_vertices.size(); ++i){
        if (_vertices[i].has_value() && _vertices[i].value() == vertex){
            return std::optional(i);
        }
    }
    return std::nullopt;
}

template <typename T>
auto hbutds::Graph<T>::add_vertex(const T& vertex) -> unsigned int{
    assert(! get_vertex_id(vertex).has_value());
    auto id{_vertices.size()};
    _vertices.push_back(vertex); // 插入顶点
    _adjacency_list.push_back({}); // 插入空出边表
    ++_vertex_size;
    return id;
}


template <typename T>
void hbutds::Graph<T>::add_edge(
    const T& source, const T& target, const double cost
){
    auto s_id {get_vertex_id(source)};
    auto t_id {get_vertex_id(target)};

    assert(s_id.has_value() && t_id.has_value()); //确认端点存在

    auto& edge_list{_adjacency_list[s_id.value()]}; //获得起点的出边表
    edge_list.push_back({.to=t_id.value(), .cost=cost}); //插入新的边
    ++_edge_size;
}

template <typename T>
auto hbutds::Graph<T>::get_edge_cost_by_id(
        const unsigned int s_id, const unsigned int t_id
) const -> double {
    auto& edge_list{_adjacency_list[s_id]};
    for(auto& e : edge_list){
        if(e.to == t_id) return e.cost;
    }
    return std::numeric_limits<double>::infinity();
}

template <typename T>
auto hbutds::Graph<T>::get_edge_cost(
        const T& source, const T& target
) const -> double{
    auto s_id {get_vertex_id(source)};
    auto t_id {get_vertex_id(target)};

    assert(s_id.has_value() && t_id.has_value()); //确认端点存在
    return get_edge_cost_by_id(s_id.value(), t_id.value());
}

template <typename T>
void hbutds::Graph<T>::remove_edge(
        const T& source, const T& target
){
    auto s_id {get_vertex_id(source)};
    auto t_id {get_vertex_id(target)};

    assert(s_id.has_value() && t_id.has_value()); //确认端点存在
    auto& edge_list{_adjacency_list[s_id.value()]};
    for(auto iter{edge_list.begin()}; iter!=edge_list.end(); ++iter){
        if((*iter).to == t_id.value()){ //查找并删除边
            edge_list.erase(iter);
            --_edge_size;
            return;
        }
    }
}

template <typename T>
void hbutds::Graph<T>::remove_vertex(const T& vertex){
    auto v_id {get_vertex_id(vertex)};
    if (! v_id.has_value()) return;

    //标记顶点已删除
    _vertices[v_id.value()] = std::nullopt;
    --_vertex_size;

    //删除这个顶点的出边表
    _adjacency_list[v_id.value()].clear();
    _edge_size -= _adjacency_list[v_id.value()].size();

    //在其他顶点的出边表中删除以这个顶点为终点的边
    for(auto& edge_list : _adjacency_list){
        for(auto iter{edge_list.begin()}; iter!=edge_list.end(); ++iter){
            if((*iter).to == v_id.value()){
                edge_list.erase(iter);
                --_edge_size;
                break;
            }
        }
    }
}

template <typename T>
void hbutds::Graph<T>::dfs_print_recursive(const T& vertex) const {
    const auto v_id{get_vertex_id(vertex)};
    assert(v_id.has_value());
    vector<bool> visited(_vertices.size(), false);
    dfs_print_recur(v_id.value(), visited);
}

template <typename T>
void hbutds::Graph<T>::dfs_print_recur(
        const unsigned int v_id, vector<bool>& visited
) const {
    cout<<format("{} ", _vertices[v_id].value());
    visited[v_id] = true;
    for(const auto& e : _adjacency_list[v_id]){
        const auto neighbor {e.to};
        if(visited[neighbor])continue;
        dfs_print_recur(neighbor, visited);
    }
}

#endif