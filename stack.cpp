#include "stack.h"
#include <iostream>
namespace hbutds{

    void stack_works(){
        hbutds::stack<int> stk;
        stk.push(1);
        stk.push(2);
        stk.push(3);
        
        assert(!stk.empty());
        assert(stk.top() == 3);
        stk.pop();
        assert(stk.top() == 2);
        stk.pop();
        assert(stk.top() == 1); 
        stk.pop();
        assert(stk.empty()); 
        std::cout<<"hbutds::stack works!\n";
    }

}