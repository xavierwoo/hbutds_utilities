#include "array.h"
#include <iostream>
using std::cout;

namespace hbutds{
    void test_access_and_size(){
        array<int, 3> arr;
        arr[0] = 0;
        arr[1] = 1;
        arr[2] = 2;
        for(int i=0; i<arr.size(); ++i){
            cout<<arr[i]<<" ";
        }
        cout<<"\nAccess and size works!\n";

    }

    void array_works(){
        test_access_and_size();
        cout<<"array_works!\n";
    }
}

