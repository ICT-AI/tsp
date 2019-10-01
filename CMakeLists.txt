cmake_minimum_required(VERSION 3.13)
project(tsp)

set(CMAKE_CXX_STANDARD 14)

add_executable(tsp src/main.cpp src/solver/AbstractSolver.cpp src/solver/AbstractSolver.h src/model/Graph.cpp src/model/Graph.h src/helper/FileHelper.cpp src/helper/FileHelper.h src/solver/BasicGreedy.cpp src/solver/BasicGreedy.h)