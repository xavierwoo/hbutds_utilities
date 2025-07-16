cmake_minimum_required(VERSION 3.10)
project(hbutds_utilities)
set(CMAKE_CXX_STANDARD 20)
add_library(hbutds_utilities STATIC
    array.h
    array.cpp
    vector.h
    vector.cpp
    forward_list.h
    forward_list.cpp
    list.h
    list.cpp
    algorithm.h
    algorithm.cpp
    stack.h
    stack.cpp
    queue.h
    queue.cpp
    binary_tree.h
    binary_tree.cpp
    tree.h
)
target_include_directories(hbutds_utilities PUBLIC "${CMAKE_CURRENT_LIST_DIR}")