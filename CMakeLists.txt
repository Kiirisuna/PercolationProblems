cmake_minimum_required(VERSION 3.7)
project(PercolationProblems)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-fopenmp")

set(SOURCE_FILES main.cpp percolation.cpp percolation.h NodeBond.cpp NodeBond.h)
add_executable(PercolationProblems ${SOURCE_FILES})
