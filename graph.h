#ifndef HBUTDS_GRAPH_H
#define HBUTDS_GRAPH_H

#include "vector.h"
#include <optional>
#include <cassert>
#include <limits>
#include <iostream>
#include <format>
#include "stack.h"
#include "queue.h"
#include <utility>
#include "algorithm.h"

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
        
        //通过顶点编号获取顶点
        auto get_vertex(const unsigned int) const -> const T&;

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

        // 深度优先迭代算法
        void dfs_print_iterative(const T&) const;

        // 判断连通性
        auto is_connected() const -> bool;
        auto dfs_count(const unsigned int, vector<bool>&) const -> unsigned int;

        // 获得深度优先路径
        auto get_dfs_path(const T&, const T&) const -> vector<T>;
        void get_dfs_tree(
                const unsigned int, vector<bool>&, 
                vector<std::optional<unsigned int>>&) const;

        // 从生成树中获得路径
        auto get_path_from_tree(
                const unsigned int, const unsigned int, 
                vector<std::optional<unsigned int>>&) const -> vector<T>;

        // 广度优先迭代算法
        void bfs_print_iterative(const T&) const;

        // 获得广度优先路径
        auto get_bfs_path(const T&, const T&) const -> vector<T>;
        auto get_bfs_tree(const unsigned int) const -> vector<std::optional<unsigned int>>;


        /*最小生成树*/
        //普里姆算法
        auto prim(const T&) const -> std::pair<vector<std::optional<unsigned int>>, double>;
        auto find_min_unvisited_v(const vector<bool>&, const vector<double>&) 
                const -> std::optional<unsigned int>;

        //克鲁斯卡尔算法
        auto kruskal() 
                const -> std::pair<vector<std::tuple<unsigned int, unsigned int, double>>, double>;
        //获得所有无向边信息，只能用于无向图（双向图）
        auto get_all_undirected_edges_info() 
                const -> vector<std::tuple<unsigned int, unsigned int, double>>;

        
        /*最短路径算法*/
        //单源最短路径树生成算法
        auto dijkstra(const T&) const -> std::pair<vector<std::optional<unsigned int>>, vector<double>>; 
        
        //获取最短路径
        auto shortest_path(const T&, const T&) const -> std::pair<vector<T>, double>;
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
auto hbutds::Graph<T>::get_vertex(const unsigned int id) const -> const T&{
    assert(_vertices[id].has_value());
    return _vertices[id].value();
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

template <typename T>
void hbutds::Graph<T>::dfs_print_iterative(
        const T& vertex
) const {
    const auto start_id{get_vertex_id(vertex)};
    assert(start_id.has_value());

    vector<bool> visited(_vertices.size(), false);
    stack<unsigned int> stk;
    stk.push(start_id.value());

    while(!stk.empty()){
        const auto v_id {stk.top()}; stk.pop();
        if (visited[v_id]) continue; // 跳过已访问的顶点

        //访问并标记顶点
        cout<<format("{} ", _vertices[v_id].value());
        visited[v_id] = true;

        //将未访问的邻接点入栈
        for(const auto& e : _adjacency_list[v_id]){
            const auto neighbor{e.to};
            if(visited[neighbor]) continue;
            stk.push(neighbor);
        }
    }
}

template <typename T>
auto hbutds::Graph<T>::is_connected() const -> bool {
    unsigned int start_id{0};
    while(! _vertices[start_id].has_value()) ++start_id; //找到第一个可行id
    assert(start_id < _vertices.size());
    vector<bool> visited(_vertices.size(), false);
    return dfs_count(start_id, visited) == _vertex_size;
}

template <typename T>
auto hbutds::Graph<T>::dfs_count(
        const unsigned int v_id, vector<bool>& visited
) const -> unsigned int{
    unsigned int count{1};
    visited[v_id] = true;
    for(const auto& e : _adjacency_list[v_id]){
        const auto neighbor {e.to};
        if(visited[neighbor])continue;
        count += dfs_count(neighbor, visited);
    }
    return count;
}

template <typename T>
auto hbutds::Graph<T>::get_dfs_path(
        const T& start, const T& end
) const -> vector<T>{
    auto start_id {get_vertex_id(start)};
    assert(start_id.has_value());
    auto end_id {get_vertex_id(end)};
    assert(end_id.has_value());

    vector<bool> visisted(_vertices.size(), false);
    vector<std::optional<unsigned int>> tree(_vertices.size(), std::nullopt);

    get_dfs_tree(start_id.value(), visisted, tree);
    return get_path_from_tree(start_id.value(), end_id.value(), tree);
}

template <typename T>
void hbutds::Graph<T>::get_dfs_tree(
        const unsigned int v_id,
        vector<bool>& visited,
        vector<std::optional<unsigned int>>& tree
) const {
    visited[v_id] = true;
    for(const auto& e : _adjacency_list[v_id]){
        if(visited[e.to]) continue;
        tree[e.to] = std::optional(v_id);
        get_dfs_tree(e.to, visited, tree);
    }
}

template <typename T>
auto hbutds::Graph<T>::get_path_from_tree(
        const unsigned int start_id,
        const unsigned int end_id,
        vector<std::optional<unsigned int>>& tree
) const -> vector<T>{
    vector<T> path;
    std::optional curr(end_id);
    while(curr.has_value()){
        path.push_back(_vertices[curr.value()].value());
        curr = tree[curr.value()];
    }

    // 没有路径则清空path
    if( path[path.size() - 1] != _vertices[start_id].value() ){
        path.clear();
        return path;
    }

    // 反转path
    for(auto i{0}; i<path.size()/2; ++i){
        auto tmp {path[i]};
        path[i] = path[path.size() - 1 - i];
        path[path.size() - 1 - i] = tmp;
    }//如果使用 std::vector，这里可以使用std::reverse函数代替这个循环

    return path;
}

template <typename T>
void hbutds::Graph<T>::bfs_print_iterative(
        const T& vertex
) const {
    const auto start_id{get_vertex_id(vertex)};
    assert(start_id.has_value());

    vector<bool> will_visit(_vertices.size(), false);//将被访问标记
    queue<unsigned int> que;

    will_visit[start_id.value()] = true;
    que.push(start_id.value());
    
    while(!que.empty()){
        const auto v_id {que.front()}; que.pop();

        //访问顶点
        cout<<format("{} ", _vertices[v_id].value());

        //将未标记的邻接点入队列
        for(const auto& e : _adjacency_list[v_id]){
            const auto neighbor{e.to};
            if(will_visit[neighbor]) continue;
            will_visit[neighbor] = true; // 标记顶点
            que.push(neighbor);
        }
    }
}

template <typename T>
auto hbutds::Graph<T>::get_bfs_path(
        const T& start, const T& end
) const -> vector<T> {
    auto start_id {get_vertex_id(start)};
    assert(start_id.has_value());
    auto end_id {get_vertex_id(end)};
    assert(end_id.has_value());

    auto tree {get_bfs_tree(start_id.value())}; //获得广度优先生成树
    return get_path_from_tree(start_id.value(), end_id.value(), tree);
}

template <typename T>
auto hbutds::Graph<T>::get_bfs_tree(
        const unsigned int start_id
) const -> vector<std::optional<unsigned int>> {
    vector<bool> will_visit(_vertices.size(), false);//将被访问标记
    queue<unsigned int> que;
    vector<std::optional<unsigned int>> tree(_vertices.size(), std::nullopt);

    will_visit[start_id] = true;
    que.push(start_id);
    
    while(!que.empty()){
        const auto v_id {que.front()}; que.pop();

        //将未标记的邻接点入队列
        for(const auto& e : _adjacency_list[v_id]){
            const auto neighbor{e.to};
            if(will_visit[neighbor]) continue;
            will_visit[neighbor] = true; // 标记顶点

            //记录顶点在生成树中的父亲
            tree[neighbor] = std::optional(v_id);
            que.push(neighbor);
        }
    }
    return tree;
}
    
template <typename T>
auto hbutds::Graph<T>::prim(
        const T& start
) const -> std::pair<vector<std::optional<unsigned int>>, double> {
    auto start_id {get_vertex_id(start)};
    assert(start_id.has_value());

    vector<std::optional<unsigned int>> tree(
            _vertices.size(), std::nullopt); // 父亲表示法存储最小生成树
    vector<double> distance(_vertices.size(), 
            std::numeric_limits<double>::infinity()); // 树外点到树的距离
    vector<bool> visited(_vertices.size(), false); //访问标记
    double tree_weight{0.0};

    distance[start_id.value()] = 0.0; // 起点一定在生成树树中，距离为0

    for(int i=0; i<_vertex_size; ++i){
        const auto curr {find_min_unvisited_v(visited, distance)};
        if(!curr.has_value()) break;

        // 将当前点添加到生成树中，tree数组中已记录了连接边
        const auto curr_id {curr.value()};
        tree_weight += distance[curr_id];
        visited[curr_id] = true;

        for(const auto& e : _adjacency_list[curr_id]){
            const auto u {e.to};
            if(visited[u] || e.cost >= distance[u]) continue;

            //更新这个点到生成树的距离和连接边
            distance[u] = e.cost;
            tree[u] = curr;
        }
    }
    return std::make_pair(tree, tree_weight);
}

template <typename T>
auto hbutds::Graph<T>::find_min_unvisited_v(
        const vector<bool>& visited,
        const vector<double>& distance
) const -> std::optional<unsigned int> {
    unsigned int min_index{std::numeric_limits<unsigned int>::max()};
    double min{std::numeric_limits<double>::infinity()};

    for(auto i{0}; i<visited.size(); ++i){
        if(!visited[i] && distance[i] < min){
            min = distance[i];
            min_index = i;
        }
    }

    return min == std::numeric_limits<double>::infinity() ?
            std::nullopt : std::optional(min_index);
}


struct EdgeCompare{
    auto operator()(
            std::tuple<unsigned int, unsigned int, double>& a,
            std::tuple<unsigned int, unsigned int, double>& b
    ) -> bool{
        return std::get<2>(a) > std::get<2>(b);
    }
};

template <typename T>   
auto hbutds::Graph<T>::kruskal(
)const -> std::pair<vector<std::tuple<unsigned int, unsigned int, double>>, double>{
    vector<std::tuple<unsigned int, unsigned int, double>> tree_edges;
    double tree_weight{0.0};

    auto all_edges {get_all_undirected_edges_info()};//获取所有无向边
    make_heap(all_edges, EdgeCompare()); //所有边信息整理成堆

    vector<int> d_set(_vertices.size(), -1);//初始化并查集

    while(all_edges.size() > 0){
        //从堆中取权值最小边
        auto e {all_edges[0]};
        pop_heap(all_edges, EdgeCompare());
        all_edges.erase(all_edges.end() + (-1));

        auto [i,j,cost] {e};
        while(d_set[i] >= 0) i=d_set[i]; // 找到起点所在树的代表顶点
        while(d_set[j] >= 0) j=d_set[j]; // 找到终点所在树的代表顶点

        if(i == j) continue; //起点和终点属于同一个树，忽略这条边
        if(i < j){ //将终点所在集合并到起点所在集合
            d_set[i] += d_set[j];
            d_set[j] = i;
        }else{ //将起点所在集合并到终点所在集合
            d_set[j] += d_set[i];
            d_set[i] = j;
        }
        tree_edges.push_back(e);
        tree_weight += cost;
        if(tree_edges.size() == _vertex_size)break;
    }
    return std::make_pair(tree_edges, tree_weight);
}

template <typename T>
auto hbutds::Graph<T>::get_all_undirected_edges_info(
)const -> vector<std::tuple<unsigned int, unsigned int, double>>{
    vector<std::tuple<unsigned int, unsigned int, double>> all_edges;
    for(int i{0}; i<_vertices.size(); ++i){
        if( ! _vertices[i].has_value()) continue;
        for(const auto& e : _adjacency_list[i]){
            if(e.to < i)continue;
            all_edges.push_back(std::make_tuple(i, e.to, e.cost));
        }
    }
    return all_edges;
}

template <typename T>
auto hbutds::Graph<T>::dijkstra(
        const T& start
) const -> std::pair<vector<std::optional<unsigned int>>, vector<double>> {
    auto start_id {get_vertex_id(start)};
    assert(start_id.has_value());

    vector<std::optional<unsigned int>> tree(
            _vertices.size(), std::nullopt); // 父亲表示法存储单源最短路径生成树
    vector<double> distance(_vertices.size(), 
            std::numeric_limits<double>::infinity()); // 到起点的距离
    vector<bool> visited(_vertices.size(), false); //访问标记

    distance[start_id.value()] = 0.0; //起点到起点的距离为0

    for(int i{0}; i<_vertex_size; ++i){
        const auto curr {find_min_unvisited_v(visited, distance)};
        if(!curr.has_value()) break;

        const auto curr_id {curr.value()};
        visited[curr_id] = true;

        for(const auto& e : _adjacency_list[curr_id]){
            const auto u {e.to};
            const auto new_distance {distance[curr_id] + e.cost};
            if(visited[u] || new_distance >= distance[u]) continue;

            distance[u] = new_distance;
            tree[u] = curr;
        }
    }
    return std::make_pair(tree, distance);
}

template <typename T>
auto hbutds::Graph<T>::shortest_path(
        const T& start, const T& end
)const -> std::pair<vector<T>, double>{
    const auto start_id {get_vertex_id(start)};
    const auto end_id {get_vertex_id(end)};
    assert(start_id.has_value() && end_id.has_value());
    auto [tree, distance] {dijkstra(start)};
    auto path {get_path_from_tree(start_id.value(), end_id.value(), tree)};
    return std::make_pair(path, distance[end_id.value()]);
}

#endif