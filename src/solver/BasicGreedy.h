#ifndef TSP_BASICGREEDY_H
#define TSP_BASICGREEDY_H

#include <list>
#include "AbstractSolver.h"
#include "./tool/Euclidean.h"

using namespace std;

class BasicGreedy: public AbstractSolver {
 protected:
  Euclidean *eucl = new Euclidean();

 protected:
  /**
   * Solve TSP of current graph.
   * Use basic greedy algorithm(nearest neighbor).
   */
  void solve() override;
};

#endif //TSP_BASICGREEDY_H
