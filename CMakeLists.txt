cmake_minimum_required(VERSION 3.17)
project(PrcessAndThread)

set(CMAKE_CXX_STANDARD 14)

add_executable(PrcessAndThread main.cpp)

find_package(Threads)

target_link_libraries(PrcessAndThread ${CMAKE_THREAD_LIBS_INIT})