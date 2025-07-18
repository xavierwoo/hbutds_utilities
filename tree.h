#ifndef HBUTDS_TREE_H
#define HBUTDS_TREE_H

#include "vector.h"
#include "stack.h"
#include <iostream>
#include <format>

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

    /*深度优先后根遍历递归算法*/
    template <typename T>
    void tree_dfs_pre_order_iterative(const TreeNode<T>&);
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

#endif