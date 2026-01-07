#ifndef HBUTDS_VECTOR_H
#define HBUTDS_VECTOR_H

#include <cassert>
#include <initializer_list>

namespace hbutds{

    template <typename T>
    struct vector{
    private:
        T* _data{nullptr}; // 数据块指针
        unsigned int _size{0}; // 当前元素个数
        unsigned int _capacity{0}; // 当前容量
    
    public:
        vector() = default; // 使用默认构造函数
        ~vector(); // 析构函数
        vector(const std::initializer_list<T>&); // 初始化列表构造函数

        void reserve(const unsigned int); // 申请容量
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
void hbutds::vector<T>::reserve(const unsigned int new_c){
    assert(new_c > _capacity);
    auto new_data {new T[new_c]}; // 申请新内存空间

    // 依次将数据元素拷贝到新内存空间
    for (int i{0}; i<_size; ++i){
        new_data[i] = _data[i];
    }

    delete[] _data; // 删除原内存空间
    _data = new_data;
    _capacity = new_c;
}

template <typename T>
hbutds::vector<T>::~vector(){
    delete[] _data;
}

template <typename T>
auto hbutds::vector<T>::operator[](const unsigned int pos) -> T&{
    assert(pos < _size);
    return _data[pos];
}

template <typename T>
hbutds::vector<T>::vector(const std::initializer_list<T>& l){
    if(l.size() == 0) return; // 若初始化列表为空，则不做任何操作
    reserve(l.size()); // 申请表空间

    // 依次将初始化列表中的元素拷贝到当前表中
    unsigned int i{0};
    for(auto it{l.begin()}; it!=l.end(); ++i, ++it){
        _data[i] = *it;
    }
    _size = l.size();
}

#endif