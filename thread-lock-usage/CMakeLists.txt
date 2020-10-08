cmake_minimum_required(VERSION 3.17)
project(thread_lock_usage C)

set(CMAKE_C_STANDARD 11)

add_executable(thread_lock_usage counter.c linklist.c)

set(GCC_COVERAGE_COMPILE_FLAGS "-pthread")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
