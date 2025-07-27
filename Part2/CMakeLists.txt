cmake_minimum_required(VERSION 3.31)
project(Part2)
find_package(CURL CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 20)

add_executable(Part2 main.cpp)
target_link_libraries(Part2 PRIVATE CURL::libcurl)
