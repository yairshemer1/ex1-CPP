cmake_minimum_required(VERSION 3.14)
project(ex1)

set(CMAKE_CXX_STANDARD 14)

add_executable(ex1 GField.h GField.cpp GFNumber.h GFNumber.cpp IntegerFactorization.cpp)