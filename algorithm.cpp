#include "algorithm.h"
#include "stack.h"
#include "vector.h"
#include <iostream>
#include <format>


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

    EightQueenSolver::EightQueenSolver(){
        for(int& e : Y) e = -1;
        for(bool& e : X) e = false;
        for(bool& e : XaY) e = false;
        for(bool& e : XmY) e = false;
    }

    void EightQueenSolver::place_recursion(int y){
        if(y == 8){ // 已放置完8个皇后，找到一个解
            result.push_back(Y);
            return;
        }

        //在第y行上从左到右依次尝试放置皇后
        for(int x{0}; x<8; ++x){
            //不考虑非法的放置
            if(X[x] == 1 || XaY[x+y] || XmY[x-y+7]) continue;

            Y[y] = x; //记录y行放置的位置
            
            //记录三条占用线
            X[x] = 1;
            XaY[x+y] = true;
            XmY[x-y+7] = true;

            //递归放置下一行
            place_recursion(y+1);

            //回溯
            X[x] = 0;
            XaY[x+y] = false;
            XmY[x-y+7] = false;
        }
    }

    void EightQueenSolver::solve(){
        place_recursion(0);
    }

    // void EightQueenSolver::print() const {
    //     cout<<format("There are {} solutions!\n", result.size());

    //     int no{0};
    //     for(auto& sol : result){
    //         cout<<format("No.{}:\n", no);
    //         ++no;

    //         for(int y{0}; y<8; ++y){
    //             for(int x{0}; x<8; ++x){
    //                 if(x != sol[y]) cout<<" #";

    //             }
    //         }
    //     }
    // }
}