#ifndef TSP_ABSTRACTSOLVER_H
#define TSP_ABSTRACTSOLVER_H

#include <vector>
#include <chrono>
#include <algorithm>
#include <limits.h>
#include "../model/Graph.h"
#include "../helper/Timer.h"

using namespace std;

#define LL_MAX 0x7FFFFFFFFFFFFFFFLL

class AbstractSolver {
 protected:
  /**
   * Graph to solve TSP
   */
  Graph *graph = nullptr;

  /**
   * Final cost of TSP
   */
  float cost = (float)INT_MAX;

  /**
   * Actual iteration of TSP solving
   */
  int actualIteration = 0;

  /**
   * Final solution tour
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
  virtual void solve(Timer &timer, long long iteration) = 0;

  void solve(Timer &timer);

  void setGraph(Graph *g);

  float getCost();

  int getActualIteration();

  vector<Node>& getTour();
};

#endif //TSP_ABSTRACTSOLVER_H
