cmake_minimum_required(VERSION 3.19)
project(LinearAlgebra)

set(CMAKE_CXX_STANDARD 11)

add_executable(linear main.cpp util/Fraction.cpp util/Fraction.h
        util/num_process.cpp util/num_process.h
        util/Matrix.cpp util/Matrix.h LinearAlgebra.cpp LinearAlgebra.h)

add_executable(Test_Fraction test/test_fraction.cpp util/Fraction.cpp util/Fraction.h
        util/num_process.cpp util/num_process.h)

add_executable(Test_Matrix test/test_matrix.cpp util/Fraction.cpp util/Fraction.h
        util/num_process.cpp util/num_process.h
        util/Matrix.cpp util/Matrix.h)