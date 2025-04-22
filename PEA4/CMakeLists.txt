cmake_minimum_required(VERSION 3.28)
project(PEA4)

set(CMAKE_CXX_STANDARD 17)

add_executable(PEA4 main.cpp
        Config.cpp
        Config.h
        DistMatrix.cpp
        DistMatrix.h
        App.cpp
        App.h
        GeneticAlgo.cpp
        GeneticAlgo.h)
