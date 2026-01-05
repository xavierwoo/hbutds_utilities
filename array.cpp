#include "array.h"
#include <iostream>
using std::cout;

namespace hbutds{
    void test_access_and_size(){
        array<int, 3> arr;
        arr[0] = 0;
        arr[1] = 1;
        arr[2] = 2;
        assert(arr.size() == 3);
        assert(arr[0] + arr[1] + arr[2] == 3);
        cout<<"\tAccess and size works!\n";
    }

    void test_array_initializer(){
        array<int, 3> arr{1,2};
        assert(arr[0] == 1);
        assert(arr[1] == 2);
        assert(arr[2] == 0);
        cout<<"\tInitializer works!\n";
    }

    void test_array_iterator(){
        array<int, 3> arr{1,2,3};
        auto it{arr.begin()};
        assert(*it == 1);
        ++it;
        assert(*it == 2);
        ++it;
        assert(*it == 3);
        ++it;
        assert(!( it != arr.end()));
        cout<<"\tIterator works!\n";
    }

    void test_array_iterator_advanced(){
        array<int, 3> arr{1,2,3};
        auto it(arr.begin() + 1);
        assert(*it == 2);
        auto it2{it - 1};
        assert(*it2 == 1);
        assert((it - it2) == 1);
        cout<<"\tAdvanced Iterator works!\n";
    }

    void test_const_array(){
        const array<int, 3> arr{1,2,3};
        assert(arr[1] == 2);
        auto it{arr.begin()};
        assert(*it == 1);
        ++it;
        assert(*it == 2);
        cout<<"\tConst array works!\n";
    }

    void array_works(){
        cout<<"Testing hbutds::array advanced version:\n";
        test_access_and_size();
        test_array_initializer();
        test_array_iterator_advanced();
        test_const_array();
        cout<<"\thbutds::array works!\n";
    }
}

