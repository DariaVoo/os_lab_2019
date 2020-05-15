cmake_minimum_required(VERSION 3.15)
project(src C)

set(CMAKE_C_STANDARD 11)

add_executable(src
        Makefile
        tcpclient.c
        tcpserver.c
        udpclient.c
        udpserver.c)
