cmake_minimum_required(VERSION 3.15)
project(src C)

set(CMAKE_C_STANDARD 11)

add_executable(src
        deadlock.c
        factorial.c
        factorial.h
        mutex.c)
