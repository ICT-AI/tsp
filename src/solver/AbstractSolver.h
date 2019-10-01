#ifndef TSP_ABSTRACTSOLVER_H
#define TSP_ABSTRACTSOLVER_H

#include <vector>
#include <chrono>
#include "../model/Graph.h"

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
  int cost;

  /**
   * Elapsed time for TSP
   */
  double elapsedTime;

  /**
   * Solution tour
   */
  vector<int> tour;

 protected:
  /**
   * Solve TSP of current graph.
   * Core algorithm for solving TSP is here.
   * You should implement this function.
   */
  virtual void solve() = 0;

 public:
  /**
   * Default destructor
   */
  virtual ~AbstractSolver() = default;

  /**
   * Solve TSP and measure elapsed time.
   */
  void solveAndMeasureTime();

  void setGraph(Graph *g);

  int getCost();

  double getElapsedTime();

  vector<int> getTour();
};

#endif //TSP_ABSTRACTSOLVER_H
