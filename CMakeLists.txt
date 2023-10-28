cmake_minimum_required(VERSION 3.25)
project(discrete_math C)

set(CMAKE_C_STANDARD 11)

add_executable(discrete_math main.c lab3_1/lab3_1.c lab3_1/lab3_1.h matrix/matrix.c matrix/matrix.h)
