#ifndef TSP_NEIGHBOURMANAGER_H
#define TSP_NEIGHBOURMANAGER_H

#include <deque>
#include <utility>
#include <chrono>
#include <random>

using namespace std;

class NeighbourManager {
 private:
  deque<pair<int, int>> neighbours;

 public:
  void initialize(int count);

  void initializeAsRandom(int count);

  bool isEmpty();

  pair<int, int> popNeighbour();
};

#endif //TSP_NEIGHBOURMANAGER_H
