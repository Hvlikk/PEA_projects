cmake_minimum_required(VERSION 3.28)
project(PEA_1)

set(CMAKE_CXX_STANDARD 17)

add_executable(PEA_1 main.cpp
        main.cpp
        CompleteInspection/CompleteInspectionTSP.cpp
        CompleteInspection/CompleteInspectionTSP.h
        ClosestNeighbour/ClosestNeighbourTSP.cpp
        ClosestNeighbour/ClosestNeighbourTSP.h
        RandomInspection/RandomInspectionTSP.cpp
        RandomInspection/RandomInspectionTSP.h
        Application.cpp
        Application.h
        DistanceMatrix.cpp
        DistanceMatrix.h
)
