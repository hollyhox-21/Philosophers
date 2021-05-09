cmake_minimum_required(VERSION 3.19)
project(Philosophers C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-Wall -Wextra -Werror")

add_executable(Philosophers main.c)
add_executable(test_time test.c test.c)