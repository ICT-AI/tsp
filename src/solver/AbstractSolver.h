#ifndef TSP_ABSTRACTSOLVER_H
#define TSP_ABSTRACTSOLVER_H

#include <vector>
#include <chrono>
#include <algorithm>
#include <limits.h>
#include "../model/Graph.h"
#include "../helper/Timer.h"
#include "../solver/tool/Euclidean.h"

using namespace std;

#define LL_MAX 0x7FFFFFFFFFFFFFFFLL

class AbstractSolver {
 protected:
  /**
   * Graph to solve TSP
   */
  Graph *graph = nullptr;

  /**
   * Best cost
   */
  double cost = (double)INT_MAX;

  /**
   * Actual iteration of TSP solving
   */
  long long actualIteration = 0;

  /**
   * Best tour
   */
  vector<Node> tour;

  /**
   * Tool for calculating euclidean distance
   */
  Euclidean *eucl = new Euclidean();

 public:
  /**
   * Default constructor
   */
  AbstractSolver() = default;

  /**
   * Default destructor
   */
  ~AbstractSolver() = default;

  /**
   * Solve TSP of current graph.
   * Core algorithm for solving TSP is here.
   * You should implement this function.
   */
  virtual void solve(Timer &timer, long long iteration) = 0;

  void solve(Timer &timer);

  void setGraph(Graph *g);

  double getCost();

  long long getActualIteration();

  bool verifyTour();

  vector<Node>& getTour();
};

#endif //TSP_ABSTRACTSOLVER_H
