cmake_minimum_required(VERSION 3.17)
project(concurrency_mapreduce C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(concurrency_mapreduce mapreduce.h bst.c common_thread.h)
set(GCC_COVERAGE_COMPILE_FLAGS "-pthread")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )