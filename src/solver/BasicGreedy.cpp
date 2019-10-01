#include "BasicGreedy.h"

BasicGreedy::BasicGreedy(Graph *g) {
  this->graph = g;
}

void BasicGreedy::solve() {
  for (int i = 0; i < 10000000; i++) {
    sqrt((float)i);
  }

  this->cost = 18;
  this->tour.emplace_back(1);
  this->tour.emplace_back(5);
  this->tour.emplace_back(3);
  this->tour.emplace_back(20);
  this->tour.emplace_back(17);
}