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
        int i{0};
        for(auto it{vec.begin()}; it != vec.end(); ++i, ++it){
            assert(*it == vec[i]);
        }
        cout<<"@ Iterator works\n";
        for(int e : vec){
            cout<<format("{} ", e);
        }
        cout<<"\nCheck the output to see if for each works\n";
    }

    void test_vector_insert(){
        vector<int> vec{1, 2, 3};
        auto it1 {vec.insert(vec.begin(), 0)};
        assert(*it1 == 0);
        auto it2 {vec.insert(vec.begin() + 2, 9)};
        assert(*it2 == 9);
        auto it3 {vec.insert(vec.end(), 10)};
        assert(*it3 == 10);

        assert(vec.size() == 6);
        assert(vec[0] == 0);
        assert(vec[1] == 1);
        assert(vec[2] == 9);
        assert(vec[3] == 2);
        assert(vec[4] == 3);
        assert(vec[5] == 10);
        cout<<"@ Insert works\n";
    }

    void test_vector_erase(){
        vector<int> vec{0, 1, 2, 3, 4, 5};
        auto it1 {vec.erase(vec.begin())};
        assert(*it1 == 1);
        auto it2 {vec.erase(vec.begin()+2)};
        assert(*it2 == 4);
        auto it3 {vec.erase(vec.begin()+3)};
        assert( ! (it3 != vec.end()));

        assert(vec.size() == 3);
        assert(vec[0] == 1);
        assert(vec[1] == 2);
        assert(vec[2] == 4);
        cout<<"@ Erase works\n";
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
        test_vector_insert();
        test_vector_erase();
        cout<<"@ hbutds::vector works\n";
    }
}