cmake_minimum_required(VERSION 3.13)
project(tsp)

set(CMAKE_CXX_STANDARD 14)

add_executable(tsp src/main.cpp src/helper/FileHelper.cpp src/helper/FileHelper.h src/model/Node.h src/model/Graph.cpp src/model/Graph.h src/model/Node.cpp src/solver/tool/Euclidean.cpp src/solver/tool/Euclidean.h src/solver/AbstractSolver.cpp src/solver/AbstractSolver.h src/solver/SequentialGreedy.cpp src/solver/SequentialGreedy.h src/helper/Timer.cpp src/helper/Timer.h src/solver/BasicHillClimbing.cpp src/solver/BasicHillClimbing.h src/solver/MapSearchGreedy.cpp src/solver/MapSearchGreedy.h src/solver/MSTGreedy.cpp src/solver/MSTGreedy.h src/solver/BasicSA.cpp src/solver/BasicSA.h src/solver/AbstractGreedy.h src/solver/AbstractLocalSearch.cpp src/solver/AbstractLocalSearch.h src/solver/tool/NeighbourManager.cpp src/solver/tool/NeighbourManager.h)