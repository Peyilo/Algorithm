cmake_minimum_required(VERSION 3.19)
project(Matrix C)

set(CMAKE_C_STANDARD 99)

add_executable(Matrix main.c Matrix.c Matrix.h util/String.c util/String.h
        util/Fraction.c util/Fraction.h util/util.c util/util.h)

add_executable(Test1 test/test1.c util/util.c util/util.h)