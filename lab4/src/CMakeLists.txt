cmake_minimum_required(VERSION 3.15)
project(src C)

set(CMAKE_C_STANDARD 11)

include_directories(libarray/includes)

add_executable(src
        libarray/includes/arraylib.h
        libarray/generate_array.c
        libarray/print_arr.c
        libarray/sum_arr.c
        process_memory.c
        sum_array.c
        zombies.c)
