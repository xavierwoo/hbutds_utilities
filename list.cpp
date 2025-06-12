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
        hbutds::list<int> lst{0,1,2};
        
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

    void test_list_erase(){
        hbutds::list<int> lst {0,1,2};
        auto it {lst.erase(lst.begin())};
        assert(*it == 1);
        it = lst.erase(it);
        assert(*it == 2);
        cout<<"@ erase works\n";
    }

    void test_list_initializer(){
        hbutds::list<int> lst {0,1,2};
        auto it{lst.begin()};
        assert(*it == 0);
        ++it;
        assert(*it == 1);
        ++it;
        assert(*it == 2);
        ++it;
        assert(!(it != lst.end()));
        cout<<"@ initializer works\n";
    }

    void test_list_copy_constructor(){
        hbutds::list<int> lst1 {1,2,3}; 
        hbutds::list<int> lst2 {lst1};

        for(auto it1{lst1.begin()}, it2{lst2.begin()}; it1 != lst1.end(); ++it1, ++it2){
            assert(*it1 == *it2);
        }
        cout<<"@ copy works\n";
    }

    void test_list_move_copy(){
        hbutds::list<int> lst1 {1,2,3}; 
        hbutds::list<int> lst2 {std::move(lst1)};

        assert(!(lst1.begin() != lst1.end()));
        auto it {lst2.begin()};
        assert(*it == 1);
        ++it;
        assert(*it == 2);
        ++it;
        assert(*it == 3);
        ++it;
        assert( ! (it != lst2.end()));
        cout<<"@ move copy works\n"; 
    }

    void test_list_assignment(){
        hbutds::list<int> lst1 {1,2,3}; 
        hbutds::list<int> lst2 {4,5,6}; 
        lst2 = lst1;

        //测试两个链表是否相等
        for(auto it1{lst1.begin()}, it2{lst2.begin()}; it1 != lst1.end(); ++it1, ++it2){
            assert(*it1 == *it2);
        }

        //测试元素是否正确
        auto it {lst2.begin()};
        assert(*it == 1);
        ++it;
        assert(*it == 2);
        ++it;
        assert(*it == 3);
        ++it;
        assert( ! (it != lst2.end()));
        cout<<"@ assignment works\n"; 
    }

    void test_list_move_assignment(){
        hbutds::list<int> lst1 {1,2,3}; 
        hbutds::list<int> lst2 {4,5,6}; 
        lst2 = std::move(lst1);

        assert(!(lst1.begin() != lst1.end()));

        //测试元素是否正确
        auto it {lst2.begin()};
        assert(*it == 1);
        ++it;
        assert(*it == 2);
        ++it;
        assert(*it == 3);
        ++it;
        assert( ! (it != lst2.end()));
        cout<<"@ move assignment works\n"; 
    }

    void list_works(){
        test_list_declare();
        test_list_insert();
        test_list_iterator();
        test_list_erase();
        test_list_initializer();
        test_list_copy_constructor();
        test_list_move_copy();
        test_list_assignment();
        test_list_move_assignment();
        cout<<"hbutds::list works!\n";
    }
} 
