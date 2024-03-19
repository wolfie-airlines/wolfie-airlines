cmake_minimum_required(VERSION 3.27)
project(lab1)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab1 z01.cpp
        Book.h
        Books.h
        Authors.h
        Vector.h)
