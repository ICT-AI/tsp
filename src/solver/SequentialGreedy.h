#ifndef TSP_BASICGREEDY_H
#define TSP_BASICGREEDY_H

#include <list>
#include <deque>
#include <random>
#include "AbstractSolver.h"
#include "./tool/Euclidean.h"

using namespace std;

class SequentialGreedy: public AbstractSolver {
 protected:
  /**
   * Tool for calculating euclidean distance
   */
  Euclidean *eucl = new Euclidean();

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
  deque<int> getStartIndexList();
};

#endif //TSP_BASICGREEDY_H
