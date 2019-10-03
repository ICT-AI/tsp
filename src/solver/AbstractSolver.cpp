#include <chrono>
#include "AbstractSolver.h"

void AbstractSolver::setGraph(Graph *g) {
  this->graph = g;
}

int AbstractSolver::getCost() {
  return this->cost;
}

int AbstractSolver::getActualIteration() {
  return this->actualIteration;
}

vector<int>& AbstractSolver::getTour() {
  return this->tour;
}

