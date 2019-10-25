#include "AbstractLocalSearch.h"

void AbstractLocalSearch::initializeAsRandom() {
  this->tour.assign(this->graph->getNodes().begin(), this->graph->getNodes().end());
  unsigned seed = chrono::system_clock::now().time_since_epoch().count();

  shuffle(this->tour.begin(), this->tour.end(), default_random_engine(seed)); // uniform random shuffle
}

void AbstractLocalSearch::initializeAsSequentialGreedy(Timer &timer) {
  AbstractGreedy *solver = new SequentialGreedy();
  auto graph = new Graph();
  graph->setNodes(this->graph->getNodes());
  solver->setGraph(graph);
  solver->solve(timer, 2);

  this->tour.assign(solver->getTour().begin(), solver->getTour().end());
}

void AbstractLocalSearch::initializeAsMSTGreedy(Timer &timer) {
  AbstractGreedy *solver = new MSTGreedy();
  auto graph = new Graph();
  graph->setNodes(this->graph->getNodes());
  solver->setGraph(graph);
  solver->solve(timer, LL_MAX);

  this->tour.assign(solver->getTour().begin(), solver->getTour().end());
}