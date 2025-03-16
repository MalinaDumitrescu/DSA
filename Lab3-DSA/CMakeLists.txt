cmake_minimum_required(VERSION 3.28)
project(Lab3_DSA)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Lab3_DSA
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        Set.cpp
        Set.h
        SetIterator.cpp
        SetIterator.h
        ShortTest.cpp
        ShortTest.h)
