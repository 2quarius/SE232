cmake_minimum_required(VERSION 3.12)
project(Basic)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Basic
        Basic.cpp
        evalstate.cpp
        evalstate.h
        exp.cpp
        exp.h
        parser.cpp
        parser.h
        program.cpp
        program.h
        statement.cpp
        statement.h)
