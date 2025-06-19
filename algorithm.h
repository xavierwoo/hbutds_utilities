#ifndef HBUTDS_ALGORITHM_H
#define HBUTDS_ALGORITHM_H

#include <string>
#include <functional>
#include <vector>
#include <utility>
#include "vector.h"

namespace hbutds{

    // 字符串括号匹配
    auto check_brackets_matching(const std::string&) -> bool;

    template <typename T, typename Comparator>
    void percolate_up(vector<T>&, int, Comparator);

    template <typename T, typename Comparator = std::less<T>>
    void push_heap(vector<T>&, Comparator = Comparator());

    void heap_works();
}


template <typename T, typename Comparator>
void hbutds::percolate_up(vector<T>& heap, int pos, Comparator cmp){
    int curr_pos {pos};
    int parent_pos {(curr_pos - 1) / 2};
    while(curr_pos > 0 && !cmp(heap[curr_pos], heap[parent_pos])){
        T tmp{std::move(heap[curr_pos])};
        heap[curr_pos] = std::move(heap[parent_pos]);
        heap[parent_pos] = std::move(tmp);
        curr_pos = parent_pos;
        parent_pos = (curr_pos - 1) / 2;
    }
}

template <typename T, typename Comparator>
void hbutds::push_heap(vector<T>& heap, Comparator cmp){
    percolate_up(heap, heap.size() - 1, cmp);
}

#endif