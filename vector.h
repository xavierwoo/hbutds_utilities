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

        struct iterator; // 迭代器结构体
        auto begin() -> iterator; // 返回首元素迭代器
        auto end() -> iterator; // 返回表终止位迭代器
        auto insert(const iterator, const T&) -> iterator; // 插入元素
        auto erase(const iterator) -> iterator; // 删除元素
        void push_back(const T&); //在尾部插入元素

        //五规则函数
        vector(const vector&); // 拷贝构造函数
        vector(vector&&);      // 移动拷贝构造函数
        auto operator=(const vector&) -> vector&; // 赋值操作符
        auto operator=(vector&&) -> vector&;      // 移动赋值操作符


        // 后续课程代码中作为常量使用
        struct const_iterator;
        auto begin() const -> const_iterator;
        auto end() const -> const_iterator;
        auto operator[](const unsigned int) const -> const T&;
    };

    template <typename T>
    struct vector<T>::iterator{
        friend vector;
    private:
        T* _ptr; // 指向元素的指针
        iterator(T* p):_ptr(p){} // 设置构造函数私有，防止私开迭代器
    public:
        auto operator++() -> iterator&; // 获得后继迭代器
        auto operator*() -> T&; // 获得指向的元素
        auto operator!=(const iterator) const -> bool; // 不等判定
        auto operator+(int) -> iterator; // 获取相对位置的迭代器

        auto operator-(const iterator) const -> int; // 计算两个迭代器的相对位置
    };

    template <typename T>
    struct vector<T>::const_iterator{
        friend vector;
    private:
        const T* _ptr;
        const_iterator(T* p):_ptr(p){}
    public:
        auto operator++() -> const_iterator&;
        auto operator*() const -> const T&;
        auto operator!=(const const_iterator) const -> bool;
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
auto hbutds::vector<T>::operator[](const unsigned int pos) const -> const T&{
    assert(pos < _size);
    return _data[pos];
}

template <typename T>
void hbutds::vector<T>::reserve(const unsigned int new_c){
    if(new_c == _capacity) return;
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
    _data = nullptr;
    _size = 0;
    _capacity = 0;
}

template <typename T>
auto hbutds::vector<T>::insert(const iterator it, const T& new_e) -> iterator{
    auto pos {it._ptr - _data}; // 需要先计算pos，扩容后it会失效
    assert(pos >= 0 && pos <= _size);

    if(_capacity == 0) reserve(1); // 模拟std::vector的扩容模式
    else if (_size == _capacity) reserve(_size * 2);

    ++_size;

    for(auto i{_size - 1}; i>pos; --i){ // 从后往前依次移动元素
        new (&_data[i]) T(std::move(_data[i-1]));
    }
    new (&_data[pos]) T(new_e); // 将新元素放在空出的位置上
    
    return iterator(_data + pos);
}

template <typename T>
void hbutds::vector<T>::push_back(const T& new_e){
    insert(end(), new_e);
}

template <typename T>
auto hbutds::vector<T>::erase(const iterator it) -> iterator{
    auto pos {it._ptr - _data}; // 计算删除位置pos
    assert(pos >= 0 && pos < _size); 

    if(pos < _size - 1){
        for(auto i{pos}; i<_size - 1; ++i){ // 从前往后依次移动元素
            _data[i] = std::move(_data[i+1]);
        }
    }else{ // 如果是删除尾元素，需要手动调用它的析构函数防止内存泄露
        _data[pos].~T();
    }

    --_size;
    return iterator(_data + pos);
}


/* 以下为五规则相关函数 */

template <typename T>
hbutds::vector<T>::vector(const vector& o){
    reserve(o.size());
    for(int i{0}; i<o._size; ++i){
        push_back(o._data[i]);
    }
}

template <typename T>
hbutds::vector<T>::vector(vector&& o):
        _data(o._data), 
        _size(o._size),
        _capacity(o._capacity){

    o._data = nullptr;
    o._size = 0;
    o._capacity = 0;
}

template <typename T>
auto hbutds::vector<T>::operator=(const vector& o) -> vector&{
    for(int i{0}; i<_size; ++i){ // 删除当前表上的所有元素
        _data[i].~T();
    }
    _size = 0;
    if(_capacity < o._size){ // 如果容量比被拷贝表小则扩容
        reserve(o._size);
    }
    for(int i{0}; i<o._size; ++i){ // 依次插入元素
        push_back(o._data[i]);
    }
    return *this;
}

template <typename T>
auto hbutds::vector<T>::operator=(vector&& o) -> vector& {
    for(int i{0}; i<_size; ++i){
        _data[i].~T();
    }
    std::free(_data);
    _data = o._data;
    _size = o._size;
    _capacity = o._capacity;
    o._data = nullptr;
    o._size = 0;
    o._capacity = 0;
    return *this;
}


/* 以下为迭代器相关函数 */

template <typename T>
auto hbutds::vector<T>::begin() -> iterator{
    return iterator(_data);
}

template <typename T>
auto hbutds::vector<T>::begin() const -> const_iterator{
    return const_iterator(_data);
}

template <typename T>
auto hbutds::vector<T>::end() -> iterator{
    return iterator(_data + _size);
}

template <typename T>
auto hbutds::vector<T>::end() const -> const_iterator{
    return const_iterator(_data + _size);
}

template <typename T>
auto hbutds::vector<T>::iterator::operator++() -> iterator&{
    ++_ptr;
    return *this;
}

template <typename T>
auto hbutds::vector<T>::iterator::operator*() -> T&{
    return *_ptr;
}

template <typename T>
auto hbutds::vector<T>::iterator::operator!=(const iterator o) const -> bool{
    return _ptr != o._ptr;
}

template <typename T>
auto hbutds::vector<T>::iterator::operator+(const int offset) -> iterator{
    return iterator(_ptr + offset);
}

template <typename T>
auto hbutds::vector<T>::iterator::operator-(const iterator o) const -> int{
    return _ptr - o._ptr;
}

template <typename T>
auto hbutds::vector<T>::const_iterator::operator++() -> const_iterator&{
    ++_ptr;
    return *this;
}

template <typename T>
auto hbutds::vector<T>::const_iterator::operator*() const -> const T&{
    return *_ptr;
}

template <typename T>
auto hbutds::vector<T>::const_iterator::operator!=(const const_iterator o) const -> bool{
    return _ptr != o._ptr;
}

#endif