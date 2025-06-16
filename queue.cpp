#include "queue.h"
#include <iostream>


void hbutds::queue_works(){
    hbutds::queue<int> que;
    que.push(1);
    que.push(2);
    que.push(3);

    assert(!que.empty());
    assert(que.front() == 1);
    que.pop();
    assert(que.front() == 2);
    que.pop();
    assert(que.front() == 3);
    que.pop();
    assert(que.empty());
    std::cout<<"hbutds::queue works!\n";
}