cmake_minimum_required(VERSION 3.15)
project(revert_string C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -L -lft")

include_directories(.)

add_executable(revert_string
        main.c
        revert_string.c
        ft_strlen.c
        revert_string.h)
