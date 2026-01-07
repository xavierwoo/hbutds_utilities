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

    void vector_works(){
        cout<<"Testing hbutds::vector simple version:\n";   
        test_vector_reserve();
        test_vector_initializer_and_access();
        cout<<"\thbutds::vector works!\n";
    }
}

