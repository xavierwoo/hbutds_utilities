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

    void test_vector_iterator(){
        vector<int> vec{1, 2, 3};
        for(auto it{vec.begin()}; it != vec.end(); ++it){
            cout<<format("{} ", *it);
        }
        cout<<"\nCheck the output to see if iterator works\n";
        for(int e : vec){
            cout<<format("{} ", e);
        }
        cout<<"\nCheck the output to see if iterator works\n";
    }

    void vector_works(){
        test_vector_initializer();
        test_vector_iterator();
        cout<<"@ hbutds::vector works\n";
    }
}