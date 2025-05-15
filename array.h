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
        array() = default;
        ~array() = default;
        array(const array& o) = default;
        array(array&&) = default;
        auto operator=(const array&) -> array& = default;
        auto operator=(array&&) -> array& = default;

        array(const std::initializer_list<T>&);
        
        auto operator[](const unsigned int) -> T&;
        auto size() const -> unsigned int;
    };

    void array_works();
    
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