#include "algorithm.h"
#include "stack.h"

auto hbutds::check_brackets_matching(const std::string& str) -> bool{
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