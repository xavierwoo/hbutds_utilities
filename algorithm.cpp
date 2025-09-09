#include "algorithm.h"
#include "stack.h"
#include "vector.h"
#include "queue.h"
#include <iostream>
#include <format>
#include <cassert>
#include <cmath>


namespace hbutds{
    using std::cout, std::format;

    auto check_brackets_matching(const std::string& str) -> bool{
        stack<char> stk;
        for(char c : str){
            switch (c) {
                case '(':
                case '[':
                case '{':
                    stk.push(c);
                    break;
                case ')':
                    if (stk.empty()) return false;
                    if (stk.top() != '(') return false;
                    stk.pop();
                    break;
                case ']':
                    if (stk.empty()) return false;
                    if (stk.top() != '[') return false;
                    stk.pop();
                    break;
                case '}':
                    if (stk.empty()) return false;
                    if (stk.top() != '{') return false;
                    stk.pop();
                    break;
            }
        }
        return stk.empty();
    }

    void test_push_heap(){
        hbutds::vector<int> heap{21, 20, 12, 22};
        push_heap(heap);
        assert(heap[0] == 22);
        assert(heap[1] == 21);
        assert(heap[2] == 12);
        assert(heap[3] == 20);
        cout<<"@ push_heap works\n";
    }

    void test_pop_heap(){
        hbutds::vector<int> heap{22, 21, 12, 20}; 
        pop_heap(heap);
        assert(heap[0] == 21);
        assert(heap[1] == 20);
        assert(heap[2] == 12);
        assert(heap[3] == 22);
        cout<<"@ pop_heap works\n";
    }

    void test_make_heap(){
        vector<int> heap{12,8,7,17};
        make_heap(heap);
        assert(heap[0] == 17);
        assert(heap[1] == 12);
        assert(heap[2] == 7);
        assert(heap[3] == 8);
        cout<<"@ make_heap works\n";
    }

    void heap_works(){
        test_push_heap();
        test_pop_heap();
        test_make_heap();
        cout<<"hbutds heap works!\n";
    }
}

auto hbutds::sqrt(double value) -> double{
    assert(value >= 0);
    auto low{0.0};
    auto high{value};

    const double error{0.00001};
    auto last_mid{value};

    while(true){
        auto mid {(low+high)/2.0};
        auto mid_sq{mid*mid};
        if(mid_sq < value){
            low = mid;
        }else if(mid_sq > value){
            high = mid;
        }else{
            return mid;
        }
        if(std::abs(last_mid - mid) < error){ //std::abs需要<cmath>头文件
            return mid;
        }
        last_mid = mid;
    }
    assert(false); //应该不会执行到这里
}