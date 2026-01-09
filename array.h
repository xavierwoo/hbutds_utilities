#ifndef HBUTDS_ARRAY_H
#define HBUTDS_ARRAY_H

#include<cassert>
#include<utility>

namespace hbutds{

    template<typename T, unsigned int N>
    struct array{        
        T data[N];
        auto operator[](unsigned int) -> T&;
        auto operator[](unsigned int) const -> const T&;
        auto size() const -> unsigned int;

        struct iterator; // 迭代器类声明
        auto begin() -> iterator; // 获取首元素迭代器
        auto end() -> iterator; // 获取终止位置迭代器

        struct const_iterator; // const迭代器声明
        auto begin() const -> const_iterator; // 获取首元素const迭代器
        auto end() const -> const_iterator; // 获取终止位置const迭代器
    };

    template<typename T, unsigned int N>
    struct array<T, N>::iterator{
        friend array;
    private:
        T* _ptr; // 指向元素的指针
        iterator(T* p):_ptr(p){} // 设置构造函数私有，防止私开迭代器
    public:
        auto operator++() -> iterator&; // 获取后继元素的迭代器
        auto operator*() -> T&; // 获取迭代器所指元素
        auto operator!=(iterator) const -> bool; //判断与某迭代器是否不等

        auto operator--() -> iterator&; // 获取前序元素的迭代器
        auto operator+(int) const -> iterator; // 通过加法获得相对位置的迭代器
        auto operator-(int) const -> iterator; // 通过减法获得相对位置的迭代器
        auto operator-(iterator) const -> int; // 获得两迭代器的相对位置
    };

    template<typename T, unsigned int N>
    struct array<T, N>::const_iterator{
        friend array;
    private:
        const T* _ptr; //指向元素的const指针
        const_iterator(const T* p):_ptr(p){};
    public:
        auto operator++() -> const_iterator&; //获取后继元素的const迭代器
        auto operator*() const -> const T&; // 获取迭代器所指元素
        auto operator!=(const_iterator) const -> bool; //判断与某const迭代器是否不等
    };


    void array_works();

}


template<typename T, unsigned int N>
auto hbutds::array<T, N>::operator[](const unsigned int pos) -> T&{
    assert(pos < N);
    return data[pos];    
}

template<typename T, unsigned int N>
auto hbutds::array<T, N>::operator[](const unsigned int pos) const -> const T&{
    assert(pos < N);
    return data[pos];    
}

template<typename T, unsigned int N>
auto hbutds::array<T, N>::size() const -> unsigned int{
    return N;
}

template<typename T, unsigned int N>
auto hbutds::array<T, N>::begin() -> iterator {
    return iterator(data);
}

template<typename T, unsigned int N>
auto hbutds::array<T, N>::end() -> iterator {
    return iterator(data+N);
} 


/***************迭代器***************/

template<typename T, unsigned int N>
auto hbutds::array<T, N>::begin() const -> const_iterator {
    return const_iterator(data);
}

template<typename T, unsigned int N>
auto hbutds::array<T, N>::end() const -> const_iterator {
    return const_iterator(data+N);
} 

template<typename T, unsigned int N>
auto hbutds::array<T, N>::iterator::operator++() -> iterator& {
    ++_ptr;
    return *this;
}

template<typename T, unsigned int N>
auto hbutds::array<T, N>::iterator::operator--() -> iterator& {
    --_ptr;
    return *this;
}

template<typename T, unsigned int N>
auto hbutds::array<T, N>::iterator::operator+(int offset) const -> iterator {
    return iterator(_ptr + offset);
}

template<typename T, unsigned int N>
auto hbutds::array<T, N>::iterator::operator-(int offset) const -> iterator {
    return iterator(_ptr - offset);
}

template<typename T, unsigned int N>
auto hbutds::array<T, N>::iterator::operator-(iterator o) const -> int {
    return _ptr - o._ptr;
}

template<typename T, unsigned int N>
auto hbutds::array<T, N>::iterator::operator*() -> T& {
    return *_ptr;
}

template<typename T, unsigned int N>
auto hbutds::array<T, N>::iterator::operator!=(const iterator o) const -> bool {
    return _ptr != o._ptr;
}

template<typename T, unsigned int N>
auto hbutds::array<T, N>::const_iterator::operator++() -> const_iterator& {
    ++_ptr;
    return *this;
}

template<typename T, unsigned int N>
auto hbutds::array<T, N>::const_iterator::operator*() const -> const T& {
    return *_ptr;
}

template<typename T, unsigned int N>
auto hbutds::array<T, N>::const_iterator::operator!=(
        const const_iterator o
) const -> bool {
    return _ptr != o._ptr;
}

#endif