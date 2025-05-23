#ifndef HBUTDS_ARRAY_H
#define HBUTDS_ARRAY_H

#include <cassert>
#include <initializer_list>
namespace hbutds{

    template<typename T, unsigned int N>
    struct array{
                
    private:
        T _data[N];
    public:

        //设定默认的五规则函数
        array() = default; // 默认构造函数
        ~array() = default; // 析构函数
        array(const array& o) = default; // 拷贝构造函数
        array(array&&) = default; // 移动拷贝构造函数
        auto operator=(const array&) -> array& = default; // =操作符
        auto operator=(array&&) -> array& = default; // 移动=操作符

        //初始化列表构造函数
        array(const std::initializer_list<T>&);
        
        //使用下标获得相应位置元素
        auto operator[](const unsigned int) -> T&;
        //获取数组长度
        auto size() const -> unsigned int;

        struct iterator; // 迭代器结构体
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
        auto operator++() -> iterator&; // 获得后继迭代器
        auto operator*() -> T&; // 获得指向的元素
        auto operator!=(const iterator) const -> bool; // 不等判定
    };

    void array_works();
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

template<typename T, unsigned int N>
hbutds::array<T, N>::array(const std::initializer_list<T>& l){
    assert(l.size() <= N);
    unsigned int i{0};
    for(auto it{l.begin()}; it!=l.end(); ++i, ++it){
        new(&_data[i]) T(*it);
    }
    for(;i<N;++i){
        new(&_data[i]) T();
    }
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

#endif