cmake_minimum_required(VERSION 2.8.4)
project(primes)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    include/calculator.hpp
    src/calculator.cpp
    src/main.cpp)

add_executable(primes ${SOURCE_FILES})