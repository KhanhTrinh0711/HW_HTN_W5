cmake_minimum_required(VERSION 4.3)
project(w1)

set(CMAKE_CXX_STANDARD 20)

add_executable(w1 main.cpp
        Src/main.c
        Src/startup.c
        Src/b1.c
        Src/b1.c)
