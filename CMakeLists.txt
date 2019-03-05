cmake_minimum_required(VERSION 3.9)
project(472a1)

set(CMAKE_CXX_STANDARD 11)

add_executable(472a1
        BFS.cpp
        BFS.h
        main.cpp
        Node.cpp
        Node.h
        Puzzle.cpp
        Puzzle.h
        puzzleDFS.txt DFS.cpp DFS.h A_Star.cpp A_Star.h)
