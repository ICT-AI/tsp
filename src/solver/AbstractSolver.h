#ifndef TSP_ABSTRACTSOLVER_H
#define TSP_ABSTRACTSOLVER_H

#include <vector>
#include <chrono>
#include <algorithm>
#include <limits.h>
#include "../model/Graph.h"
#include "../helper/Timer.h"

using namespace std;

class AbstractSolver {
 protected:
  /**
   * Graph to solve TSP
   */
  Graph *graph;

  /**
   * Cost of TSP
   */
  int cost = INT_MAX;

  /**
   * Actual iteration of TSP solving
   */
  int actualIteration = 0;

  /**
   * Solution tour
   */
  vector<Node> tour;

 public:
  /**
   * Default constructor
   */
  AbstractSolver() = default;

  /**
   * Default destructor
   */
  virtual ~AbstractSolver() = default;

  /**
   * Solve TSP of current graph.
   * Core algorithm for solving TSP is here.
   * You should implement this function.
   */
  virtual void solve(int iteration, Timer &timer) = 0;

  void setGraph(Graph *g);

  int getCost();

  int getActualIteration();

  vector<int> getTour();
};

#endif //TSP_ABSTRACTSOLVER_H
