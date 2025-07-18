#ifndef HBUTDS_TREE_H
#define HBUTDS_TREE_H

#include "vector.h"
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

    template <typename T>
    void tree_dfs_pre_order_recursive(const TreeNode<T>&);
}

template <typename T>
void hbutds::tree_dfs_pre_order_recursive(const TreeNode<T>& root){
    cout<<format("{} ", root.data);
    for(const auto& child : root.children){
        tree_dfs_pre_order_recursive(child);
    }
}



#endif