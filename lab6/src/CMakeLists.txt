cmake_minimum_required(VERSION 3.15)
project(src C)

set(CMAKE_C_STANDARD 11)

add_executable(src
        client.c
        server.c

        libfactorial/factorial.c
        libfactorial/factorial.h
        libfactorial/mult_modulo.c)
