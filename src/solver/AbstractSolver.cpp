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

vector<int> AbstractSolver::getTour() {
  vector<int> tour_index;
  tour_index.reserve(this->graph->getNodes().size());

  for (auto node : this->tour) {
    tour_index.push_back(node.index);
  }

  return tour_index;
}

