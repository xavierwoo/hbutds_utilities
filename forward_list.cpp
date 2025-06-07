#include "forward_list.h"
#include <cassert>
#include <iostream>

namespace hbutds{
    using std::cout;
    void test_forward_list_push_front(){
        hbutds::forward_list<int> lst;
        lst.push_front(1);
        lst.push_front(2);
        lst.push_front(3);

        auto it{lst.begin()};
        assert(*it == 3);
        ++it;
        assert(*it == 2);
        ++it;
        assert(*it == 1);
        cout<<"@ push_front works\n";
    }

    void test_forward_list_insert_after(){
       hbutds::forward_list<int> lst;
        lst.push_front(1);
        lst.push_front(2); 
        auto rit {lst.insert_after(lst.begin(), 0)};
        assert(*rit == 0);

        auto it{lst.begin()};
        assert(*it == 2);
        ++it;
        assert(*it == 0);
        ++it;
        assert(*it == 1);
        cout<<"@ insert_after works\n"; 
    }

    

    void test_forward_list_erase_after(){
        hbutds::forward_list<int> lst;
        lst.push_front(1);
        lst.push_front(2);
        lst.push_front(3);
        auto rit {lst.erase_after(lst.begin())};
        assert(*rit == 1);
        auto it{lst.begin()};
        assert(*it == 3);
        ++it;
        assert(*it == 1);
        cout<<"@ erase_after works\n";
    }

    void test_forward_list_reverse(){
        hbutds::forward_list<int> lst;
        lst.push_front(1);
        lst.push_front(2);
        lst.push_front(3);
        lst.reverse();
        auto it {lst.begin()};
        assert(*it == 1);
        ++it;
        assert(*it == 2);
        ++it;
        assert(*it == 3);
        ++it;
        assert( ! (it != lst.end()));
        cout<<"@ reverse works\n";
    }

    void forward_list_works(){
        test_forward_list_push_front();
        test_forward_list_insert_after();
        test_forward_list_erase_after();
        test_forward_list_reverse();
    }

}