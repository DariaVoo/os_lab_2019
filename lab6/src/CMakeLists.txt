cmake_minimum_required(VERSION 3.15)
project(src C)

set(CMAKE_C_STANDARD 11)

include_directories(libfactorial)

add_executable(src
        libfactorial/factorial.c
        libfactorial/factorial.h
        libfactorial/get_next_line.c
        libfactorial/mult_modulo.c
        client.c
        server.c)
