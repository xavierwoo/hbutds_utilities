#ifndef HBUTDS_ARRAY_H
#define HBUTDS_ARRAY_H

#include<cassert>

namespace hbutds{

    template<typename T, unsigned int N>
    struct array{        
    private:
        T _data[N];
    public:
        auto operator[](const unsigned int) -> T&;
        auto size() const -> unsigned int;

        struct iterator; // 迭代器类声明
        auto begin() -> iterator; // 获取首元素迭代器
        auto end() -> iterator; // 获取终止位置迭代器
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
        auto operator!=(const iterator) const -> bool; //判断与某迭代器是否不等
    };


    void array_works();

}


template<typename T, unsigned int N>
auto hbutds::array<T, N>::operator[](const unsigned int pos) -> T&{
    assert(pos < N);
    return _data[pos];    
}

template<typename T, unsigned int N>
auto hbutds::array<T, N>::size() const -> unsigned int{
    return N;
}

template<typename T, unsigned int N>
auto hbutds::array<T, N>::begin() -> iterator {
    return iterator(_data);
}

template<typename T, unsigned int N>
auto hbutds::array<T, N>::end() -> iterator {
    return iterator(_data+N);
} 

template<typename T, unsigned int N>
auto hbutds::array<T, N>::iterator::operator++() -> iterator& {
    ++_ptr;
    return *this;
}

template<typename T, unsigned int N>
auto hbutds::array<T, N>::iterator::operator*() -> T& {
    return *_ptr;
}

template<typename T, unsigned int N>
auto hbutds::array<T, N>::iterator::operator!=(const iterator o) const -> bool {
    return _ptr != o._ptr;
}

#endif