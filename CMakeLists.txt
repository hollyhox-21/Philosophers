cmake_minimum_required(VERSION 3.17.5)
project(Philosophers C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-Wall -Wextra -Werror")

add_executable(Philosophers main.c actions.c utils.c enter_point.c)
add_executable(test_time test.c test.c)