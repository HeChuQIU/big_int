cmake_minimum_required(VERSION 3.26)
project(integer_calculator)

set(CMAKE_CXX_STANDARD 23)

include_directories(.)

add_executable(integer_calculator
        calculator.cpp
        calculator.h
        double_circular_linked_list.h
        double_circular_linked_list.cpp
        big_int.h
        big_int.cpp
        )

add_subdirectory(Google_tests)
