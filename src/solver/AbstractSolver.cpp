#include <chrono>
#include "AbstractSolver.h"

void AbstractSolver::solveAndMeasureTime() {
  chrono::system_clock::time_point start = chrono::system_clock::now(); // timer start
  this->solve();  // solve TSP
  chrono::system_clock::time_point end = chrono::system_clock::now(); // timer end
  chrono::duration<double> time = end - start;

  this->elapsedTime = time.count();
}

void AbstractSolver::setGraph(Graph *g) {
  this->graph = g;
}

int AbstractSolver::getCost() {
  return this->cost;
}

double AbstractSolver::getElapsedTime() {
  return this->elapsedTime;
}

vector<int> AbstractSolver::getTour() {
  return this->tour;
}

