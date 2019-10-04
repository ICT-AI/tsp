#include <chrono>
#include "AbstractSolver.h"

void AbstractSolver::solve(Timer &timer) {
  this->solve(timer, LL_MAX);
}

void AbstractSolver::setGraph(Graph *g) {
  this->graph = g;
}

float AbstractSolver::getCost() {
  return this->cost;
}

int AbstractSolver::getActualIteration() {
  return this->actualIteration;
}

vector<Node>& AbstractSolver::getTour() {
  return this->tour;
}

