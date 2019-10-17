#include "NeighbourManager.h"

void NeighbourManager::initialize(int count) {
  this->neighbours.clear();

  int i, j;
  for (i = 0; i < count - 1; i++) {
    for (j = i + 1; j < count; j++) {
      this->neighbours.emplace_back(i, j);
    }
  }
}

void NeighbourManager::initializeAsRandom(int count) {
  this->initialize(count);
  unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  shuffle(this->neighbours.begin(), this->neighbours.end(), default_random_engine(seed)); // uniform random shuffle
}

bool NeighbourManager::isEmpty() {
  return this->neighbours.empty();
}

pair<int, int> NeighbourManager::popNeighbour() {
  pair<int, int> neighbour = this->neighbours.front();
  this->neighbours.pop_front();

  return neighbour;
}