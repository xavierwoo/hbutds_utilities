#ifndef HBUTDS_BINARY_TREE_H
#define HBUTDS_BINARY_TREE_H

#include "vector.h"
#include "stack.h"
#include <iostream>

namespace hbutds{

    template <typename T>
    struct BinaryTreeNode{
        T data;  // 数据元素
        BinaryTreeNode* left{nullptr}; // 左孩子指针
        BinaryTreeNode* right{nullptr}; // 右孩子指针

        BinaryTreeNode() = default;
        BinaryTreeNode(const T& d): data(d){}
        BinaryTreeNode(const T& d, BinaryTreeNode* l, BinaryTreeNode* r):
                data(d), left(l), right(r){}
    };

    auto make_huffman_tree(const vector<double>&) -> BinaryTreeNode<double>*;

    template <typename T>
    void binary_tree_pre_order_recursive(const BinaryTreeNode<T>* const);

}


template <typename T>
void hbutds::binary_tree_pre_order_recursive(const BinaryTreeNode<T>* const root){
    if (root == nullptr) return;
    std::cout<<root->data<<" ";
    binary_tree_pre_order_recursive(root->left);
    binary_tree_pre_order_recursive(root->right);
}


#endif