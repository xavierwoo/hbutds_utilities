#include "vector.h"
#include <format>
#include <iostream>

namespace hbutds{
    using std::cout, std::format;
    void test_vector_initializer(){
        vector<int> vec{1, 2, 3};
        assert(vec.size() == 3);
        assert(vec.capacity() == 3);
        assert(vec[0] == 1);
        assert(vec[1] == 2);
        assert(vec[2] == 3);
        cout<<"@ vector initializer, [] operator, size() and capacity() works\n";
    }

    void vector_works(){
        test_vector_initializer();
        cout<<"@ hbutds::vector works\n";
    }
}