cmake_minimum_required(VERSION 3.28)
project(dsa5)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(dsa5
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        ShortTest.cpp
        ShortTest.h
        SMMIterator.cpp
        SMMIterator.h
        SortedMultiMap.cpp
        SortedMultiMap.h)
