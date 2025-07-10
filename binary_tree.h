#ifndef HBUTDS_BINARY_TREE_H
#define HBUTDS_BINARY_TREE_H

#include "vector.h"
#include "stack.h"
#include <iostream>
#include <format>

using std::cout, std::format;

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

    template <typename T>
    void binary_tree_pre_order_iterative(const BinaryTreeNode<T>* const);

}


template <typename T>
void hbutds::binary_tree_pre_order_recursive(const BinaryTreeNode<T>* const root){
    if (root == nullptr) return;
    cout<<format("{} ", root->data);
    binary_tree_pre_order_recursive(root->left);
    binary_tree_pre_order_recursive(root->right);
}

template <typename T>
void hbutds::binary_tree_pre_order_iterative(const BinaryTreeNode<T>* const root){
    if (root == nullptr) return;
    stack<const  BinaryTreeNode<T>*> stk;
    stk.push(root);
    while(! stk.empty()){
        auto curr {stk.top()}; stk.pop();
        cout<<format("{} ", curr->data);
        if(curr->right != nullptr) stk.push(curr->right);
        if(curr->left != nullptr) stk.push(curr->left);
    } 
}

#endif