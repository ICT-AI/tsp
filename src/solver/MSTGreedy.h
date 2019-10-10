#ifndef TSP_MSTGREEDY_H
#define TSP_MSTGREEDY_H

#include <stack>
#include "AbstractSolver.h"
#include "./tool/Euclidean.h"

class MSTGreedy: public AbstractSolver {
 protected:
  /**
   * Tool for calculating euclidean distance
   */
  Euclidean *eucl = new Euclidean();

  vector<deque<int>> mst;

  vector<int> oddIndices;

  vector<int> eulerian;

 protected:
  /**
   * Solve TSP of current graph.
   * Use basic greedy algorithm(nearest neighbor).
   */
  void solve(Timer &timer, long long iteration) override;

  void primMST();

  void findOddIndices();

  void perfectMatching();

  void makeEulerian();

  void makeHamiltonian();
};

#endif //TSP_MSTGREEDY_H
