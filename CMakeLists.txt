#需求的最低cmake程序版本
cmake_minimum_required(VERSION 3.12)

#本工程的名称
project(Algorithm)

#本工程支持的C++版本
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")

add_subdirectory(Sort)
add_subdirectory(Heap)
add_subdirectory(Search)
add_subdirectory(UnionFind)
add_subdirectory(Tree)
add_subdirectory(Graph)
add_subdirectory(OJCode)
