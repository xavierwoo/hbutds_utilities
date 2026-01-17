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

        void reserve(unsigned int); // 申请容量
        auto size() const -> unsigned int; // 获取元素个数
        auto capacity() const -> unsigned int; // 获取表容量
        auto operator[](unsigned int) -> T&; // 使用[]访问元素
        auto operator[](unsigned int) const -> const T&;

        struct iterator;
        auto begin() -> iterator; // 返回首元素迭代器
        auto end() -> iterator; // 返回表终止位迭代器

        auto insert(iterator, const T&) -> iterator; // 插入元素
        void push_back(const T&); // 在尾部插入元素
        auto erase(iterator) -> iterator; // 删除元素
    };

    template <typename T>
    struct vector<T>::iterator{
        friend vector;
    private:
        T* _ptr; // 指向元素的指针
        iterator(T* p):_ptr(p){}; // 设置构造函数私有，防止私开迭代器
    public:
        auto operator++() -> iterator&; // 获得后继迭代器
        auto operator*() -> T&; // 获得指向的元素
        auto operator!=(const iterator) const -> bool; // 不等判定
        auto operator+(int) const -> iterator; // 获得相对位置靠后的迭代器
        auto operator-(int) const -> iterator; // 获得相对位置靠前的迭代器
        auto operator-(iterator) const -> int; // 获得迭代器相对位置
        auto operator--() -> iterator&; // 获得前序迭代器
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
auto hbutds::vector<T>::operator[](const unsigned int pos) const -> const T&{
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

template <typename T>
auto hbutds::vector<T>::begin() -> iterator{
    return iterator(_data);
}

template <typename T>
auto hbutds::vector<T>::end() -> iterator{
    return iterator(_data + _size);
}

template <typename T>
auto hbutds::vector<T>::insert(const iterator it, const T& new_e) -> iterator{
    auto pos {it._ptr - _data}; // 需要先计算pos，扩容后it会失效
    assert(pos >= 0 && pos <= _size);

    if(_capacity == 0) {reserve(1);} // 模拟std::vector的扩容模式
    else if (_size == _capacity) {reserve(_size * 2);}

    ++_size;

    // 从后往前依次移动元素
    for(auto i{_size - 1}; i>pos; --i){ 
        _data[i] = _data[i-1];
    }
    _data[pos] = new_e; // 将新元素放在空出的位置上
    
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

    for(auto i{pos}; i<_size - 1; ++i){ // 从前往后依次移动元素
        _data[i] = _data[i+1];
    }
    --_size;
    return iterator(_data + pos); // 返回指向删除元素后一位的迭代器
}


/***************迭代器***************/

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
auto hbutds::vector<T>::iterator::operator+(const int offset) const -> iterator{
    return iterator(_ptr + offset);
}

template <typename T>
auto hbutds::vector<T>::iterator::operator-(const int offset) const -> iterator{
    return iterator(_ptr - offset);
}

template <typename T>
auto hbutds::vector<T>::iterator::operator-(const iterator o) const -> int{
    return _ptr - o._ptr;
}

template <typename T>
auto hbutds::vector<T>::iterator::operator--() -> iterator&{
    --_ptr;
    return *this;
}


#endif