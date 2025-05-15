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


#endif