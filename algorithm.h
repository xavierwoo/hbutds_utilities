#ifndef HBUTDS_ALGORITHM_H
#define HBUTDS_ALGORITHM_H

#include <string>
#include <functional>
#include <vector>
#include <utility>
#include <cassert>
#include <filesystem>
#include <algorithm>
#include "vector.h"

namespace hbutds{

    // 字符串括号匹配
    auto check_brackets_matching(const std::string&) -> bool;

    // 堆元素向上调整
    template <typename T, typename Comparator>
    void percolate_up_heap(vector<T>&, const int, Comparator);

    // 堆插入元素
    template <typename T, typename Comparator = std::less<T>>
    void push_heap(vector<T>&, Comparator = Comparator());

    // 堆元素向下调整
    template <typename T, typename Comparator>
    void percolate_down_heap(vector<T>&, const int, const int, Comparator);

    // 弹出堆顶
    template <typename T, typename Comparator = std::less<T>>
    void pop_heap(vector<T>&, Comparator = Comparator());

    // 将vector调整为堆
    template <typename T, typename Comparator = std::less<T>>
    void make_heap(vector<T>&, Comparator = Comparator());

    void heap_works();


    //顺序查找
    template<typename List, typename Checker>
    auto find_if(List&, Checker) -> List::iterator;

    //二分查找
    template<typename List, typename T, typename Comparator = std::less<T>>
    auto binary_search(const List&, T, Comparator = Comparator())-> bool;

    //二分查找求开根号
    auto sqrt(double) -> double;

    //直接选择排序
    template<typename List>
    void selection_sort(List&);

    //堆排序
    template<typename List>
    void heap_sort(List&);

    //冒泡排序
    template<typename List>
    void bubble_sort(List&);

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

template <typename T, typename Comparator>
void hbutds::make_heap(vector<T>& heap, Comparator cmp){
    for(int pos=heap.size()/2-1; pos >= 0; --pos){
        percolate_down_heap(heap, pos, heap.size(), cmp);
    }
}

template<typename List, typename Checker>
auto hbutds::find_if(List& v, Checker checker) -> List::iterator{
    for(auto it{v.begin()}; it!=v.end(); ++it){
        if(checker(*it)){
            return it;
        }
    }
    return v.end();
}

template<typename List, typename T, typename Comparator>
auto hbutds::binary_search(const List& list, T value, Comparator cmp) -> bool{
    int low{0};
    int high{static_cast<int>(list.size()) - 1};
    while(low <= high){
        int mid {(low+high)/2};
        if(cmp(list[mid], value)){
            low = mid + 1;
        }else if (cmp(value, list[mid])){
            high = mid - 1;
        }else{
            return true;
        }
    }
    return false;
}

template<typename List>
void hbutds::selection_sort(List& list){
    for(auto i{0}; i<list.size(); ++i){
        auto min_index{i};

        //找到未排序的最小元素
        for(auto j{i+1}; j<list.size(); ++j){
            if(list[j] < list[min_index]){
                min_index = j;
            }
        }

        //将最小元素与未排序的起始位置元素交换
        auto tmp {list[min_index]};
        list[min_index] = list[i];
        list[i] = tmp;
    }
}


template<typename List>
void hbutds::heap_sort(List& list){
    std::make_heap(list.begin(), list.end());//将顺序表调整为堆

    for(auto last{list.end()}; last != list.begin(); last = last + (-1)){
        std::pop_heap(list.begin(), last);
    }
}

template<typename List>
void hbutds::bubble_sort(List& list){
    for(auto i{0}; i<list.size() - 1; ++i){
        bool never_swapped {true};//是否交换过的标记
        for(auto j{0}; j<list.size() - i - 1; ++j){
            if (list[j] <= list[j+1]) continue;
            auto tmp{list[j]};
            list[j] = list[j+1];
            list[j+1] = tmp;
            never_swapped = false;
        }
        if(never_swapped) return;//如果没有交换，则说明已经有序
    }
}

#endif