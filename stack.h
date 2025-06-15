#ifndef HBUTDS_STACK_H
#define HBUTDS_STACK_H

#include "vector.h"
#include <cassert>

namespace hbutds{
    
    template <typename T>
    struct stack{
    private:
        vector<T> data;
    public:
        auto empty() const -> bool;
        void push(const T&);
        auto top() -> T&;
        void pop();
    };

    void stack_works();
}

template <typename T>
auto hbutds::stack<T>::empty() const -> bool {
    return data.size() == 0;
}

template <typename T>
void hbutds::stack<T>::push(const T& new_e) {
    data.push_back(new_e);
}

template <typename T>
auto hbutds::stack<T>::top() -> T&{
    assert(!empty());
    return data[data.size() - 1];
}

template <typename T>
void hbutds::stack<T>::pop(){
    assert(!empty());
    data.erase(data.begin() + (data.size() - 1));
}

#endif