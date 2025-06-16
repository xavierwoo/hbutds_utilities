#ifndef HBUTDS_QUEUE_H
#define HBUTDS_QUEUE_H

#include "list.h"
#include <cassert>

namespace hbutds{

    template <typename T>
    struct queue{
    private:
        list<T> data;
    public:
        auto empty() -> bool;
        void push(const T&);
        auto front() -> T&;
        void pop();
    };

    void queue_works();
}

template <typename T>
auto hbutds::queue<T>::empty() -> bool{
    return ! (data.begin() != data.end());
}

template <typename T>
void hbutds::queue<T>::push(const T& new_e){
    data.push_back(new_e);
}

template <typename T>
auto hbutds::queue<T>::front() -> T&{
    assert(!empty());
    return *data.begin();
}

template <typename T>
void hbutds::queue<T>::pop() {
    assert(!empty());
    data.erase(data.begin());
}

#endif