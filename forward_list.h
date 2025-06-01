#ifndef HBUTDS_FORWARD_LIST_H
#define HBUTDS_FORWARD_LIST_H

#include <utility>

namespace hbutds{

    template <typename T>
    struct forward_list{
    private:
        struct Node;  // 单链表节点
        Node* _head; // 头节点指针

    public:
        struct iterator;
        forward_list(): _head(new Node()){};
        // forward_list(const std::initializer_list<T>&); // 初始化列表构造函数

        auto begin() -> iterator; // 首元素迭代器
        auto end() -> iterator; // 终止位迭代器
        void push_front(const T&); // 在链表头插入元素
        auto insert_after(const iterator, const T&) -> iterator;
        auto erase_after(const iterator) -> iterator;
        // void reverse(); // 转置
    };

    template <typename T>
    struct forward_list<T>::Node{
        T data; // 数据域
        Node* next{nullptr}; //后继指针

        Node() = default;
        Node(const T& d): data(d){};
    };

    template <typename T>
    struct forward_list<T>::iterator{
        friend forward_list;
    private:
        Node* _curr{nullptr}; // 迭代器指针指向某节点
        iterator(Node* ptr): _curr(ptr){}
    public:
        auto operator*() -> T&;
        auto operator++() -> iterator&;
        auto operator!=(const iterator) -> bool;
    };

    void forward_list_works();
}

template <typename T>
auto hbutds::forward_list<T>::begin() -> iterator {
    return iterator(_head->next);
}

template <typename T>
auto hbutds::forward_list<T>::end() -> iterator {
    return iterator(nullptr);
}

template <typename T>
void hbutds::forward_list<T>::push_front(const T& new_e){
    auto new_node {new Node(new_e)};
    new_node->next = _head->next;
    _head->next = new_node;
}

template <typename T>
auto hbutds::forward_list<T>::insert_after(
        const iterator after_it, const T& new_e
) -> iterator {
    auto new_node {new Node(new_e)};
    new_node->next = after_it._curr->next;
    after_it._curr->next = new_node;
    return iterator(new_node);
}

template <typename T>
auto hbutds::forward_list<T>::erase_after(
        const iterator after_it
) -> iterator {
    auto del_node {after_it._curr->next};
    after_it._curr->next = del_node->next;
    delete del_node;
    return iterator(after_it._curr->next);
}


/*以下是迭代器相关实现*/

template <typename T>
auto hbutds::forward_list<T>::iterator::operator*() -> T&{
    return _curr->data;
}

template <typename T>
auto hbutds::forward_list<T>::iterator::operator++() -> iterator&{
    _curr = _curr->next;
    return *this;
}

template <typename T>
auto hbutds::forward_list<T>::iterator::operator!=(
        const iterator o
) -> bool {
    return _curr != o._curr;
}

#endif