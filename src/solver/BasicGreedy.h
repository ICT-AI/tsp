#ifndef TSP_BASICGREEDY_H
#define TSP_BASICGREEDY_H

#include "AbstractSolver.h"

using namespace std;

class BasicGreedy: public AbstractSolver {
 protected:
  /**
   * Solve TSP of current graph.
   * Use basic greedy algorithm(nearest neighbor).
   */
  void solve() override;

 public:
  BasicGreedy() = default;

  BasicGreedy(Graph *g);
};

#endif //TSP_BASICGREEDY_H
