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
        cout<<"\nCheck the output to see if for each works\n";
    }

    void test_vector_iterator_calculation(){
        vector<int> vec{1, 2, 3, 4, 5};
        assert(*(vec.begin() + 1) == vec[1]);
        assert(*(vec.begin() + 3) == vec[3]);
        cout<<"@ Iterator calculation works\n";
    }

    void vector_works(){
        test_vector_initializer();
        test_vector_iterator();
        test_vector_iterator_calculation();
        cout<<"@ hbutds::vector works\n";
    }
}