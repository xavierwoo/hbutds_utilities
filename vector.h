#ifndef HBUTDS_VECTOR_H
#define HBUTDS_VECTOR_H

#include <utility>
#include <cstdlib>
#include <cassert>

namespace hbutds{

    template <typename T>
    struct vector{
    private:
        T* _data {nullptr}; // 指向数据块
        unsigned int _size{0}; // 元素个数
        unsigned int _capacity{0}; //表容量
    public:
        vector() = default;
        ~vector();
        vector(const std::initializer_list<T>&); // 初始化列表构造函数

        void reserve(const unsigned int); // 扩容
        auto size() const -> unsigned int; // 获取元素个数
        auto capacity() const -> unsigned int; // 获取表容量
        auto operator[](const unsigned int) -> T&; // 使用[]访问元素
    };

    void vector_works();
} 

template <typename T>
auto hbutds::vector<T>::size() const -> unsigned int{
    return _size;
}

template <typename T>
auto hbutds::vector<T>::capacity() const -> unsigned int{
    return _capacity;
}

template <typename T>
auto hbutds::vector<T>::operator[](const unsigned int pos) -> T&{
    assert(pos < _size);
    return _data[pos];
}

template <typename T>
void hbutds::vector<T>::reserve(const unsigned int new_c){
    assert(new_c > _capacity); // 新容量必须大于当前容量
    auto new_data {static_cast<T*>(std::malloc(sizeof(T) * new_c))};
    for(auto i{0}; i<_size; ++i){ // 依次将元素移动拷贝到新地址
        new (&new_data[i]) T(std::move(_data[i]));
    }
    std::free(_data);
    _data = new_data;
    _capacity = new_c;
}

template <typename T>
hbutds::vector<T>::vector(const std::initializer_list<T>& l){
    if(l.size() == 0) return;
    reserve(l.size());
    unsigned int i{0};
    for(auto it{l.begin()}; it!=l.end(); ++i, ++it){
        new(&_data[i]) T(*it);
    }
    _size = l.size();
}

template <typename T>
hbutds::vector<T>::~vector(){
    for(int i{0}; i<_size; ++i){
        _data[i].~T();
    }
    std::free(_data);
}

#endif