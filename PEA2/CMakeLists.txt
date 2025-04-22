cmake_minimum_required(VERSION 3.28)
project(PEA2)

MATH(EXPR stack_size " 256 * 1024 * 1024") # 16 Mb
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--stack,${stack_size}")


set(CMAKE_CXX_STANDARD 17)

add_executable(PEA2 App/main.cpp
        App/Application.h
        App/Application.cpp
        App/DistMatrix.h
        App/DistMatrix.cpp
        Algos/Asym/LowestCostSearchAS.h
        Algos/Asym/LowestCostSearchAS.cpp
        Algos/Asym/DFSSearchAS.h
        Algos/Asym/DFSSearchAS.cpp
        Algos/Asym/BFSSearchAS.h
        Algos/Asym/BFSSearchAS.cpp
        Algos/Symetric/BFSSearchS.cpp
        Algos/Symetric/BFSSearchS.h
        Algos/Symetric/DFSSearchS.cpp
        Algos/Symetric/DFSSearchS.h
        Algos/Symetric/LCSearchS.cpp
        Algos/Symetric/LCSearchS.h
)
