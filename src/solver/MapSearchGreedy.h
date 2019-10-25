#ifndef TSP_MAPSEARCHGREEDY_H
#define TSP_MAPSEARCHGREEDY_H

#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <random>
#include "AbstractGreedy.h"

using namespace std;

class MapSearchGreedy : public AbstractGreedy {
 protected:
  /**
   * Solve TSP of current graph.
   * Use basic greedy algorithm(nearest neighbor).
   */
  void solve(Timer &timer, long long iteration) override;

  /**
   * Get randomly shuffled start node index list.
   *
   * @return
   */
  deque<Node> getStartIndexList();
};

#endif // TSP_MAPSEARCHGREEDY_H
