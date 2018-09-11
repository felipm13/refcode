cmake_minimum_required(VERSION 2.8)

project(example)
add_definitions("-std=c++11")
add_executable(example main.cpp)
target_link_libraries(example boost_system boost_filesystem)
