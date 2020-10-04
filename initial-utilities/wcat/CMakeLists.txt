cmake_minimum_required(VERSION 3.17)
project(wcat)

set(CMAKE_CXX_STANDARD 14)

add_executable(wcat wcat.c wgrep.c)
