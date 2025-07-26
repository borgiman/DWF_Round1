cmake_minimum_required(VERSION 3.31)
project(Part1)

set(CMAKE_CXX_STANDARD 20)

add_executable(Part1 main.cpp
        GutenbergHashTable.h
        GutenbergHashTable.cpp)
