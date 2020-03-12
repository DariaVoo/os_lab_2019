cmake_minimum_required(VERSION 3.15)
project(src C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(src
        find_min_max.c
        find_min_max.h
        parallel_min_max.c
        sequential_min_max.c
        utils.c
        utils.h)
