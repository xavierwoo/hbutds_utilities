#include "vector.h"
#include <format>
#include <iostream>

namespace hbutds{
    using std::cout, std::format;

    struct A{
        A(){cout<<"Default constructor\n";}
        ~A(){cout<<"Destructor\n";}
        A(const A&){cout<<"Copy constructor\n";}
        A(A&&){cout<<"Move copy constructor\n";}
        auto operator=(const A&)->A&{
            cout<<"= operator\n";
            return *this;
        }
        auto operator=(A&&) ->A&{
            cout<<"Move = operator\n";
            return *this;
        }
    };

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

    void test_vector_iterator_calculation(){
        vector<int> vec{1, 2, 3, 4, 5};
        assert(*(vec.begin() + 1) == vec[1]);
        assert(*(vec.begin() + 3) == vec[3]);
        cout<<"@ Iterator calculation works\n";
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

    void test_vector_push_back(){
        vector<int> vec;
        vec.push_back(1);
        vec.push_back(2);
        vec.push_back(3);

        assert(vec.size() == 3);
        assert(vec[0] == 1);
        assert(vec[1] == 2);
        assert(vec[2] == 3);
        cout<<"@ Push back works\n";
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

    void test_vector_rule_five(){
        vector<A> vec0{A(), A(), A()}; // 三次默认构造，三次拷贝构造，三次析构
        vector<A> vec1(vec0);  // 三次拷贝构造
        vector<A> vec2(std::move(vec1)); // 没有输出
        vector<A> vec3;
        vec2 = vec0; // 三次析构 三次拷贝构造
        vec2 = std::move(vec0); // 三次析构
        cout<<"Check the output to see if rule of five works\n";

        vector<int> vi1{1,2,3};
        vector<int> vi2{vi1};
        assert(vi1.size() == 3);
        assert(vi2.size() == 3);
        assert(vi2[0] == 1);
        assert(vi2[1] == 2);
        assert(vi2[2] == 3);
        vector<int> vi3(std::move(vi2));
        assert(vi2.size() == 0);
        assert(vi3.size() == 3);
        assert(vi3[0] == 1);
        assert(vi3[1] == 2);
        assert(vi3[2] == 3);

        vector<int> vi4;
        vi4 = vi3;
        assert(vi3.size() == 3);
        assert(vi4.size() == 3);
        assert(vi4[0] == 1);
        assert(vi4[1] == 2);
        assert(vi4[2] == 3);

        vi3.push_back(20);
        vi3 = std::move(vi4);
        assert(vi3.size() == 3);
        assert(vi4.size() == 0);
        assert(vi3[0] == 1);
        assert(vi3[1] == 2);
        assert(vi3[2] == 3);

        cout<<"@ rule of five good\n";
    }

    void vector_works(){
        test_vector_initializer();
        test_vector_iterator();
        test_vector_iterator_calculation();
        test_vector_insert();
        test_vector_push_back();
        test_vector_erase();
        test_vector_rule_five();
        
        cout<<"@ hbutds::vector works\n";
    }
}