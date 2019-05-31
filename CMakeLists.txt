cmake_minimum_required(VERSION 3.13)
project(big_integer_matrix)

set(CMAKE_CXX_STANDARD 17)

add_executable(big_integer_matrix main.cpp matrix.cpp big_integer.cpp)
