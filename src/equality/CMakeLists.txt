cmake_minimum_required(VERSION 3.1)
project(equality)

set (CMAKE_CXX_STANDARD 17)

add_executable(equality
    main.cpp
    DisjointSet.cpp
    Prover.cpp
    TermNetwork.cpp
)