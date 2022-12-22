cmake_minimum_required(VERSION 3.21)
project(DS_HW2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(DS_HW2
        wet2util.h
        worldcup23a2.cpp
        worldcup23a2.h
        Player.cpp
        Player.h
        Team.cpp
        Team.h
        AVLTree.h)
