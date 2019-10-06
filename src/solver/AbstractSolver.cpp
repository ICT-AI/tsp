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

bool AbstractSolver::verifyTour() {
  vector<int> temp;
  temp.reserve(this->tour.size());
  for (auto node : this->tour) {
    temp.push_back(node.index);
  }

  sort(temp.begin(), temp.end());
  temp.erase(unique(temp.begin(), temp.end()), temp.end());

  return (temp.size() == this->graph->getNodes().size());
}

vector<Node>& AbstractSolver::getTour() {
  return this->tour;
}

