#include "vector.h"
#include <iostream>
using std::cout;

namespace hbutds{

    void test_vector_reserve(){
        vector<int> vec;
        assert(vec.size() == 0);
        assert(vec.capacity() == 0);
        vec.reserve(5);
        assert(vec.capacity() == 5);
        assert(vec.size() == 0);
        cout<<"\tReserve works!\n";
    }

    void test_vector_initializer_and_access(){
        vector<int> vec{1,2,3};
        assert(vec.size() == 3);
        assert(vec[0] == 1);
        assert(vec[1] == 2);
        assert(vec[2] == 3);
        cout<<"\tInitializer and access works!\n";
    }

    void test_vector_iterator(){
        vector<int> vec{1,2,3};
        auto it{vec.begin()};
        assert(*it == 1);
        ++it;
        assert(*it == 2);
        ++it;
        assert(*it == 3);
        ++it;
        assert(! (it != vec.end()));
        cout<<"\tIterator works!\n";
    }

    void test_vector_iterator_calculation(){
        vector<int> vec{1,2,3};
        assert(*(vec.begin() + 2) == 3);
        assert(*(vec.end() - 2) == 2);
        cout<<"\tIterator calculation works!\n";
    }

    void test_vector_insert(){
        vector<int> vec{1,2,3};
        auto it {vec.insert(vec.begin(), 0)};
        assert(vec.size() == 4);
        assert(*it == 0);
        assert(*(it+1) == 1);
        vec.push_back(0);
        assert(vec[4] == 0);
        cout<<"\tInsert works!\n";
    }

    void test_vector_erase(){
        vector<int> vec{1,2,3};
        auto it {vec.erase(vec.begin())};
        assert(*it == 2);
        assert(vec.size() == 2);
        cout<<"\tErase works!\n";
    }

    void vector_works(){
        cout<<"Testing hbutds::vector simple version:\n";   
        test_vector_reserve();
        test_vector_initializer_and_access();
        test_vector_iterator();
        test_vector_iterator_calculation();
        test_vector_insert();
        test_vector_erase();
        cout<<"\thbutds::vector works!\n";
    }
}

