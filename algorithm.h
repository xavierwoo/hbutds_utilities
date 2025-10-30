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
    template<typename SeqList>
    void selection_sort(SeqList&);

    //堆排序
    template<typename SeqList>
    void heap_sort(SeqList&);

    //冒泡排序
    template<typename SeqList>
    void bubble_sort(SeqList&);

    //以末尾元素为轴的划分算法
    template<typename Iterator>
    auto partition(Iterator begin, Iterator end) -> Iterator;

    //快速排序
    template<typename Iterator>
    void sort(Iterator begin, Iterator end);

    //直接插入排序
    template<typename SeqList>
    void insertion_sort(SeqList&);

    //希尔排序
    template<typename SeqList>
    void shell_sort(SeqList&);
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

template<typename SeqList>
void hbutds::selection_sort(SeqList& data){
    for(auto i{0}; i<data.size(); ++i){
        auto min_index{i};

        //找到未排序的最小元素
        for(auto j{i+1}; j<data.size(); ++j){
            if(data[j] < data[min_index]){
                min_index = j;
            }
        }

        //将最小元素与未排序的起始位置元素交换
        auto tmp {data[min_index]};
        data[min_index] = data[i];
        data[i] = tmp;
    }
}


template<typename SeqList>
void hbutds::heap_sort(SeqList& data){
    std::make_heap(data.begin(), data.end());//将顺序表调整为堆

    for(auto last{data.end()}; last != data.begin(); last = last + (-1)){
        std::pop_heap(data.begin(), last);
    }
}

template<typename SeqList>
void hbutds::bubble_sort(SeqList& data){
    for(auto i{0}; i<data.size() - 1; ++i){
        bool never_swapped {true};//是否交换过的标记
        for(auto j{0}; j<data.size() - i - 1; ++j){
            if (data[j] <= data[j+1]) continue;
            auto tmp{data[j]};
            data[j] = data[j+1];
            data[j+1] = tmp;
            never_swapped = false;
        }
        if(never_swapped) return;//如果没有交换，则说明已经有序
    }
}

template<typename Iterator>
auto hbutds::partition(Iterator begin, Iterator end) -> Iterator{
    auto it_pivot {end + (-1)}; //以最后一个元素为轴
    auto it_i {begin}; //较小元素的插入位置

    for(auto it_j{begin}; it_j != end + (-1); ++it_j){
        if(*it_j >= *it_pivot) continue;

        //交换i与j位的元素
        auto tmp {*it_j};
        *it_j = *it_i;
        *it_i = tmp;

        ++it_i;
    }

    //将轴放置到正确的最终位置
    auto tmp {*it_pivot};
    *it_pivot = *it_i;
    *it_i = tmp;

    //返回指向轴的迭代器
    return it_i;
}

template<typename Iterator>
void hbutds::sort(Iterator begin, Iterator end){
    if (begin >= end) return;

    auto it_pivot {partition(begin, end)}; //划分

    hbutds::sort(begin, it_pivot); //对左边进行排序
    hbutds::sort(it_pivot+1, end); //对右边进行排序
}

template<typename SeqList>
void hbutds::insertion_sort(SeqList& data){
    if(data.size() <= 1) {return;}

    // end_pos为有序部分的终止位置
    for(auto end_pos{1}; end_pos < data.size(); ++end_pos){
        auto tmp {data[end_pos]};

        auto i {end_pos};
        
        while(i > 0 && data[i-1] > tmp){
            data[i] = data[i-1];
            --i;
        }// 向后移动比tmp大的元素，同时确定插入位置i

        data[i] = tmp;
    }
}

template<typename SeqList>
void hbutds::shell_sort(SeqList& data){
    for(auto k{data.size() / 2}; k >= 1; k/=2){

        // 将数据按照步长k分组
        for(auto group{0}; group < k; ++group){

            //针对group分组做直接插入排序
            for(auto end_pos{group + k}; end_pos < data.size(); end_pos += k){
                auto tmp {data[end_pos]};
                auto i {end_pos};
                while(i >= k && data[i - k] > tmp){
                    data[i] = data[i-k];
                    i -= k;
                }
                data[i] = tmp;
            }
        }
    }
}

#endif