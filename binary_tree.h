#ifndef HBUTDS_BINARY_TREE_H
#define HBUTDS_BINARY_TREE_H

#include "vector.h"

namespace hbutds{

    template <typename T>
    struct BinaryTreeNode{
        T data;
        BinaryTreeNode* left{nullptr};
        BinaryTreeNode* right{nullptr};

        BinaryTreeNode() = default;
        BinaryTreeNode(const T& d): data(d){};
        BinaryTreeNode(const T& d, BinaryTreeNode* l, BinaryTreeNode* r):
                data(d), left(l), right(r){};
    };

    auto make_huffman_tree(const vector<double>&) -> BinaryTreeNode<double>*;
}

#endif