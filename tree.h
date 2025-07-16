#ifndef HBUTDS_TREE_H
#define HBUTDS_TREE_H

#include "vector.h"

namespace hbutds{

    template <typename T>
    struct TreeNode{
        T data; // 存储节点元素
        vector<TreeNode> children; //存储孩子节点

        TreeNode() = default;
        TreeNode(const T& d): data(d){}
        TreeNode(const T& d, const vector<TreeNode>& cl)
                : data(d), children(cl){}
    };

}
#endif