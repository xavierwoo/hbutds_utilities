#include "list.h"
#include <iostream>
#include <cassert>

namespace hbutds{
    using std::cout;

    void test_list_insert(){
        hbutds::list<int> lst;
        auto it {lst.insert(lst.end(), 1)};
        assert(*it == 1);
        it = lst.insert(lst.begin(), 2);
        assert(*it == 2);
        it = lst.begin();
        assert(*it == 2);
        ++it;
        assert(*it == 1);
        cout<<"@ insert works\n";
    }

    void test_list_declare(){
        hbutds::list<int> lst;
        auto sit {lst.begin()};
        auto eit {lst.end()};
        assert(!(sit != eit));
        cout<<"@ declaration works\n";
    }

    void test_list_iterator(){
        hbutds::list<int> lst;
        lst.push_back(0);
        lst.push_back(1);
        lst.push_back(2);
        
        auto it{lst.begin()};
        assert(*it == 0);
        ++it;
        assert(*it == 1);
        ++it;
        assert(*it == 2);

        --it;
        assert(*it == 1);

        cout<<"@ iterator works\n";
    }

    void list_works(){
        test_list_declare();
        test_list_insert();
        test_list_iterator();
        cout<<"hbutds::list works!\n";
    }
} 
