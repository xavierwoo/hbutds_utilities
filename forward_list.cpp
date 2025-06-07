#include "forward_list.h"
#include <cassert>
#include <iostream>
#include <utility>

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

    void test_forward_list_initializer(){
        hbutds::forward_list<int> lst {1,2,3};
        auto it {lst.begin()};
        assert(*it == 1);
        ++it;
        assert(*it == 2);
        ++it;
        assert(*it == 3);
        ++it;
        assert( ! (it != lst.end()));
        cout<<"@ initializer works\n";
    }

    void test_forward_list_copy_constructor(){
        hbutds::forward_list<int> lst1 {1,2,3}; 
        hbutds::forward_list<int> lst2 {lst1};

        for(auto it1{lst1.begin()}, it2{lst2.begin()}; it1 != lst1.end(); ++it1, ++it2){
            assert(*it1 == *it2);
        }
        cout<<"@ copy works\n";
    }

    void test_forward_list_move_copy(){
        hbutds::forward_list<int> lst1 {1,2,3}; 
        hbutds::forward_list<int> lst2 {std::move(lst1)};

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

    void test_forward_list_assignment(){
        hbutds::forward_list<int> lst1 {1,2,3}; 
        hbutds::forward_list<int> lst2 {4,5,6}; 
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

    void test_forward_list_move_assignment(){
        hbutds::forward_list<int> lst1 {1,2,3}; 
        hbutds::forward_list<int> lst2 {4,5,6}; 
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


    void forward_list_works(){
        test_forward_list_push_front();
        test_forward_list_insert_after();
        test_forward_list_erase_after();
        test_forward_list_reverse();
        test_forward_list_initializer();
        test_forward_list_copy_constructor();
        test_forward_list_move_copy();
        test_forward_list_assignment();
        test_forward_list_move_assignment();
    }

}