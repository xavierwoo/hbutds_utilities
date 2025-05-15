#include "array.h"
#include <iostream>
#include <format>
#include <utility>
using std::cout, std::format;

namespace hbutds{

    struct A{
        A(){cout<<"Default constructor\n";}
        ~A(){cout<<"Deconstructor\n";}
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

    struct B{
        int data{0};
        B() = default;
        B(int b):data(b){}
    };

    void test_access_and_size(){
        array<int, 3> arr;
        arr[0] = 0;
        arr[1] = 1;
        arr[2] = 2;
        for(int i=0; i<arr.size(); ++i){
            cout<<format("{} ", arr[i]);
        }
        cout<<"\n@ Access and size works!\n";

    }

    void test_rule_of_five(){
        array<A, 3> arr0;
        auto arr1{arr0};
        auto arr2{std::move(arr0)};

        array<A, 3> arr3;
        arr3 = arr1;
        arr3 = std::move(arr1);

        cout<<"@ Check the output to see if five-rule is good\n";
    }

    void test_initializer(){
        array<int, 4> arr{1, 2, 3};
        assert(arr[0] == 1);
        assert(arr[1] == 2);
        assert(arr[2] == 3);
        assert(arr[3] == 0);

        array<B, 3> arrB{B(1), B(2)};
        assert(arrB[0].data == 1);
        assert(arrB[1].data == 2);
        assert(arrB[2].data == 0);
        cout<<"\n@ Initializer works\n";
    }

    void array_works(){
        cout<<"@ Testing hbutds::array\n";
        test_access_and_size();
        test_rule_of_five();
        test_initializer();
        cout<<"@ hbutds::array works!\n";
    }
}

