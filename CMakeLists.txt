cmake_minimum_required(VERSION 3.17)
project(johnson_algorithm)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(extern/libfort)
add_subdirectory(extern/FibHeapLib)

add_subdirectory(include)
add_subdirectory(src)
