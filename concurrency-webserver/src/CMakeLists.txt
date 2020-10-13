cmake_minimum_required(VERSION 3.17)
project(src C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(src
        io_helper.c
        io_helper.h
        request.c
        request.h
        wserver.c)
set(GCC_COVERAGE_COMPILE_FLAGS "-pthread")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
