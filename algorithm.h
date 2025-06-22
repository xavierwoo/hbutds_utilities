#ifndef HBUTDS_ALGORITHM_H
#define HBUTDS_ALGORITHM_H

#include <string>
#include <functional>
#include <vector>
#include <utility>
#include <cassert>
#include "vector.h"

namespace hbutds{

    // 字符串括号匹配
    auto check_brackets_matching(const std::string&) -> bool;

    template <typename T, typename Comparator>
    void percolate_up_heap(vector<T>&, const int, Comparator);

    template <typename T, typename Comparator = std::less<T>>
    void push_heap(vector<T>&, Comparator = Comparator());

    template <typename T, typename Comparator>
    void percolate_down_heap(vector<T>&, const int, const int, Comparator);

    template <typename T, typename Comparator = std::less<T>>
    void pop_heap(vector<T>&, Comparator = Comparator());

    void heap_works();
}


template <typename T, typename Comparator>
void hbutds::percolate_up_heap(vector<T>& heap, const int pos, Comparator cmp){
    int curr_pos {pos};
    int parent_pos {(curr_pos - 1) / 2};
    while(curr_pos > 0 && !cmp(heap[curr_pos], heap[parent_pos])){

        //交换当前节点与父亲节点的值
        T tmp{std::move(heap[curr_pos])};
        heap[curr_pos] = std::move(heap[parent_pos]);
        heap[parent_pos] = std::move(tmp);

        //更新当前节点为其父亲节点
        curr_pos = parent_pos;
        parent_pos = (curr_pos - 1) / 2;
    }
}

template <typename T, typename Comparator>
void hbutds::push_heap(vector<T>& heap, Comparator cmp){
    percolate_up_heap(heap, heap.size() - 1, cmp);
}

template <typename T, typename Comparator>
void hbutds::percolate_down_heap(
        vector<T>& heap, const int pos, const int end_pos, Comparator cmp
){
    int curr_pos{pos};
    int child_pos{curr_pos*2 + 1};
    while(child_pos < end_pos){

        // 定位到更大的孩子
        if (child_pos+1 < end_pos && cmp(heap[child_pos], heap[child_pos+1])){
            ++child_pos;
        }

        // 如果孩子更小，则已经满足堆结构
        if (!cmp(heap[curr_pos], heap[child_pos])) return;

        // 交换当前节点与孩子节点的值
        T tmp {std::move(heap[curr_pos])};
        heap[curr_pos] = std::move(heap[child_pos]);
        heap[child_pos] = std::move(tmp);

        //更新当前节点到孩子节点
        curr_pos = child_pos;
        child_pos = curr_pos*2 + 1;
    }
}

template <typename T, typename Comparator>
void hbutds::pop_heap(vector<T>& heap, Comparator cmp){
    assert(heap.size() > 0);

    //交换首尾元素
    T tmp {std::move(heap[0])};
    heap[0] = std::move(heap[heap.size() - 1]);
    heap[heap.size() - 1] = std::move(tmp);

    // 将前n-1个元素上进行0号元素向下调整
    percolate_down_heap(heap, 0, heap.size() - 1, cmp);
}


#endif