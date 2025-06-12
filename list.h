#ifndef HBUTDS_LIST_H
#define HBUTDS_LIST_H

#include <cassert>
#include <utility>

namespace hbutds{

    template <typename T>
    struct list{
    private:
        struct Node; // 双链表节点
        Node* _head; // 头节点指针
        Node* _tail; // 尾节点指针

    public:
        struct iterator; // 迭代器
        list();
        list(const std::initializer_list<T>&); // 初始化列表构造函数

        auto begin() -> iterator; // 获取首元素迭代器
        auto end() -> iterator;  // 获取终止位迭代器
        auto insert(const iterator, const T&) -> iterator; // 插入元素
        auto erase(const iterator) -> iterator; // 删除元素
        void push_back(const T&); // 在链表尾部插入元素

        //五规则函数
        ~list();
        list(const list<T>&); // 拷贝构造函数
        list(list<T>&&); // 移动拷贝构造函数
        auto operator=(const list<T>&); // 赋值操作符
        auto operator=(list<T>&&); // 移动赋值操作符
    };

    template <typename T>
    struct list<T>::Node{
        Node* prev{nullptr}; // 前序指针
        T data;              // 数据域
        Node* next{nullptr}; // 后继指针

        Node() = default;
        Node(const T& d):data(d){};
    };

    template <typename T>
    struct list<T>::iterator{
        friend list; // 使得list能够使用iterator的私有构造函数
    private:
        Node* _curr; // 迭代器指针指向某节点
        iterator(Node* c):_curr(c){}

    public:
        auto operator++() -> iterator&; // 向后迭代
        auto operator*() -> T&; // 获取所指元素
        auto operator!=(const iterator) -> bool; // 判断是否不等
        auto operator--() -> iterator&; // 向前迭代
    };

    void list_works();
}


template <typename T>
hbutds::list<T>::list(){
    _head = new Node();
    _tail = new Node();
    _head->next = _tail;
    _tail->prev = _head;
}

template <typename T>
hbutds::list<T>::list(const std::initializer_list<T>& l){
    _head = new Node();
    _tail = new Node();
    _head->next = _tail;
    _tail->prev = _head;
    for(auto& e : l){
        push_back(e);
    }
}

template <typename T>
auto hbutds::list<T>::begin() -> iterator {
    return iterator(_head->next);
}

template <typename T>
auto hbutds::list<T>::end() -> iterator {
    return iterator(_tail);
}

template <typename T>
auto hbutds::list<T>::insert(const iterator it, const T& new_e) -> iterator {
    auto node {it._curr};
    auto new_node {new Node(new_e)};
    auto prev_node {it._curr->prev};

    new_node->prev = prev_node;
    new_node->next = node;

    prev_node->next = new_node;
    node->prev = new_node;

    return iterator(new_node);
}

template <typename T>
void hbutds::list<T>::push_back(const T& new_e){
    insert(end(), new_e);
}

template <typename T>
auto hbutds::list<T>::erase(const iterator it) -> iterator {
    auto del_node {it._curr};
    assert(del_node != _head && del_node != _tail);

    auto prev_node {del_node->prev};
    auto next_node {del_node->next};

    prev_node->next = next_node;
    next_node->prev = prev_node;

    delete del_node;

    return iterator(next_node);
}


/* 五规则函数 */

template <typename T>
hbutds::list<T>::~list(){
    auto curr {_head};
    while(curr != nullptr){
        auto tmp {curr};
        curr = curr->next;
        delete tmp;
    }
}

template <typename T>
hbutds::list<T>::list(const list<T>& o){
    _head = new Node();
    _tail = new Node();
    _head->next = _tail;
    _tail->prev = _head;
    auto curr {o._head->next};
    while(curr != o._tail){
        push_back(curr->data);
        curr = curr->next;
    }
}



/* 以下是迭代器相关函数 */

template <typename T>
auto hbutds::list<T>::iterator::operator*() -> T&{
    return _curr->data;
}

template <typename T>
auto hbutds::list<T>::iterator::operator++() -> iterator&{
    _curr = _curr->next;
    return *this;
}

template <typename T>
auto hbutds::list<T>::iterator::operator!=(const iterator o) -> bool {
    return _curr != o._curr;
}

template <typename T>
auto hbutds::list<T>::iterator::operator--() -> iterator&{
    _curr = _curr->prev;
    return *this;
}

#endif