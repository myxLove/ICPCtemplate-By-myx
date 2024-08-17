cmake_minimum_required(VERSION 3.28)
project(ICPC_template)

set(CMAKE_CXX_STANDARD 17)

add_executable(ICPC_template main.cpp
        code/data-template/segmentTree.cpp
        code/data-template/pbds-template/BST.cpp)
