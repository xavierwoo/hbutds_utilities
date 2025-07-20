#ifndef HBUTDS_BINARY_TREE_H
#define HBUTDS_BINARY_TREE_H

#include "vector.h"
#include "stack.h"
#include <iostream>
#include <format>

namespace hbutds{

    using std::cout, std::format;

    template <typename T>
    struct BinaryTreeNode{
        T data;  // 数据元素
        BinaryTreeNode* left{nullptr}; // 左孩子指针
        BinaryTreeNode* right{nullptr}; // 右孩子指针

        BinaryTreeNode() = default;
        BinaryTreeNode(const T& d): data(d){}
        BinaryTreeNode(const T& d, BinaryTreeNode* l, BinaryTreeNode* r):
                data(d), left(l), right(r){}

        ~BinaryTreeNode();
    };

    /*构造哈夫曼树*/
    auto make_huffman_tree(const vector<double>&) -> BinaryTreeNode<double>*;

    /*前序遍历递归算法*/
    template <typename T>
    void binary_tree_pre_order_recursive(const BinaryTreeNode<T>* const);

    /*前序遍历迭代算法*/
    template <typename T>
    void binary_tree_pre_order_iterative(const BinaryTreeNode<T>*);

    /*求幂集*/
    template <typename T>
    auto get_power_set(const vector<T>&) -> vector<vector<T>>;

    /*求幂集函数的递归子函数*/
    template <typename T>
    void get_power_set_recur(const vector<T>&, const unsigned int, 
            vector<T>&, vector<vector<T>>&);
    
    /*中序遍历递归算法*/
    template <typename T>
    void binary_tree_in_order_recursive(const BinaryTreeNode<T>* const);

    /*中序遍历迭代算法*/
    template <typename T>
    void binary_tree_in_order_iterative(const BinaryTreeNode<T>*);

    /*汉诺塔操作求解算法*/
    void hanoi(const int, const char, const char, const char);

    /*后序遍历递归算法*/
    template <typename T>
    void binary_tree_post_order_recursive(const BinaryTreeNode<T>* const);

    /*后序遍历迭代算法*/
    template <typename T>
    void binary_tree_post_order_iterative(const BinaryTreeNode<T>*);

}


template <typename T>
void hbutds::binary_tree_pre_order_recursive(const BinaryTreeNode<T>* const root){
    if (root == nullptr) return;
    cout<<format("{} ", root->data);
    binary_tree_pre_order_recursive(root->left);
    binary_tree_pre_order_recursive(root->right);
}

template <typename T>
void hbutds::binary_tree_pre_order_iterative(const BinaryTreeNode<T>* root){
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

template <typename T>
auto hbutds::get_power_set(const vector<T>& ori_set) -> vector<vector<T>>{
    vector<vector<T>> power_set;
    vector<T> curr_set;
    get_power_set_recur(ori_set, 0, curr_set, power_set);
    return power_set;
}

template <typename T>
void hbutds::get_power_set_recur(
        const vector<T>& ori_set, 
        const unsigned int pos, 
        vector<T>& curr_set, 
        vector<vector<T>>& power_set
){
    if(pos == ori_set.size()){
        power_set.push_back(curr_set);
        return;
    }

    curr_set.push_back(ori_set[pos]); //有这个元素
    get_power_set_recur(ori_set, pos+1, curr_set, power_set);

    curr_set.erase(curr_set.end() + (-1)); //没有这个元素
    get_power_set_recur(ori_set, pos+1, curr_set, power_set);
}

template <typename T>
void hbutds::binary_tree_in_order_recursive(const BinaryTreeNode<T>* const root){
    if (root == nullptr) return;
    binary_tree_in_order_recursive(root->left);
    cout<<format("{} ", root->data);
    binary_tree_in_order_recursive(root->right);
}

template <typename T>
void hbutds::binary_tree_in_order_iterative(const BinaryTreeNode<T>* root){
    if(root == nullptr) return;
    stack<const BinaryTreeNode<T>*> stk;
    const BinaryTreeNode<T>* curr {root};
    while(curr != nullptr || !stk.empty()){

        //将curr指针移动到最左，并记录路径
        while(curr != nullptr){
            stk.push(curr);
            curr = curr->left;
        }

        //当前节点为栈顶元素
        curr = stk.top(); stk.pop();
        //访问当前节点
        cout<<format("{} ", curr->data);
        //移动至右孩子
        curr = curr->right;
    }
}

template <typename T>
void hbutds::binary_tree_post_order_recursive(const BinaryTreeNode<T>* const root){
    if(root == nullptr) return;
    binary_tree_post_order_recursive(root->left);
    binary_tree_post_order_recursive(root->right);
    cout<<format("{} ", root->data);
}

template <typename T>
void hbutds::binary_tree_post_order_iterative(const BinaryTreeNode<T>* root){
    if(root == nullptr) return;
    stack<const BinaryTreeNode<T>*> stk;
    const BinaryTreeNode<T>* curr{root};
    const BinaryTreeNode<T>* last_visited{nullptr};
    while(curr != nullptr || !stk.empty()){

        //将curr指针移动到最左，并记录路径
        while(curr != nullptr){
            stk.push(curr);
            curr = curr->left;
        }
        
        auto top_node {stk.top()};
        //检查是否有右子树需要访问
        if(top_node->right != nullptr && top_node->right != last_visited){
            curr = top_node->right;
        }else{
            //访问当前的栈顶
            cout<<format("{} ", top_node->data);
            last_visited = top_node;
            stk.pop();
        }
    }
}

template <typename T>
hbutds::BinaryTreeNode<T>::~BinaryTreeNode(){
    if (left != nullptr) delete left;
    if (right != nullptr) delete right;
}

#endif