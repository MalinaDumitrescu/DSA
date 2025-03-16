cmake_minimum_required(VERSION 3.27)
project(SetHashing)

set(CMAKE_CXX_STANDARD 17)

add_executable(SetHashing  ExtendedTest.cpp ExtendedTest.h App.cpp Set.h Set.cpp
SetIterator.cpp SetIterator.h ShortTest.cpp ShortTest.h)
