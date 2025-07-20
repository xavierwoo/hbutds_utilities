#ifndef HBUTDS_TREE_H
#define HBUTDS_TREE_H

#include "vector.h"
#include "stack.h"
#include "queue.h"
#include "array.h"
#include <iostream>
#include <format>
#include <filesystem>

namespace hbutds{

    using std::cout, std::format;

    template <typename T>
    struct TreeNode{
        T data; // 存储节点元素
        vector<TreeNode> children; //存储孩子节点

        TreeNode() = default;
        TreeNode(const T& d): data(d){}
        TreeNode(const T& d, const vector<TreeNode>& cl)
                : data(d), children(cl){}
    };

    /*深度优先先根遍历递归算法*/
    template <typename T>
    void tree_dfs_pre_order_recursive(const TreeNode<T>&);

    /*深度优先后根遍历迭代算法*/
    template <typename T>
    void tree_dfs_pre_order_iterative(const TreeNode<T>&);

    /*深度优先后根遍历递归算法*/
    template <typename T>
    void tree_dfs_post_order_recursive(const TreeNode<T>&);

        struct EightQueenSolver{
        array<int, 8> Y; // 棋子在每一行的位置
        array<bool, 8> X; // x=?这条线是否被占用
        array<bool, 15> XaY; // x+y=?这条线是否被占用
        array<bool, 15> XmY; // x-y=?这条线是否被占用

        vector<array<int, 8>> result; //所有结果

        EightQueenSolver(); //构造函数初始化
        void place_recursion(int); //递归放置棋子
        void solve(); //算法启动函数
        void print() const; //打印结果
    };

    /*广度优先遍历算法*/
    template <typename T>
    void tree_bfs(const TreeNode<T>&);

    void list_files_bfs(const std::filesystem::path& dir_path);
}

template <typename T>
void hbutds::tree_dfs_pre_order_recursive(const TreeNode<T>& root){
    cout<<format("{} ", root.data);
    for(const auto& child : root.children){
        tree_dfs_pre_order_recursive(child);
    }
}

template <typename T>
void hbutds::tree_dfs_pre_order_iterative(const TreeNode<T>& root){
    stack<const TreeNode<T>*> stk;
    stk.push(&root);

    while(!stk.empty()){
        auto curr {stk.top()}; stk.pop();
        cout<<format("{} ", curr->data);

        //若希望遍历顺序与递归方式一致，
        //此处可以逆序将孩子节点指针压入栈
        for(const auto& child : curr->children){
            stk.push(&child);
        }
    }
}

template <typename T>
void hbutds::tree_dfs_post_order_recursive(const TreeNode<T>& root){
    for(const auto& child : root.children){
        tree_dfs_post_order_recursive(child);
    }
    cout<<format("{} ", root.data);
}

template <typename T>
void hbutds::tree_bfs(const TreeNode<T>& root){
    queue<const TreeNode<T>*> que;
    que.push(&root);

    while(!que.empty()){
        auto curr {que.front()}; que.pop();
        cout<<format("{} ", curr->data);

        for(const auto& child : curr->children){
            que.push(&child);
        }
    }
}

#endif