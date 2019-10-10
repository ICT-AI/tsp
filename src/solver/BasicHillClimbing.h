#ifndef TSP_BASICHILLCLIMBING_H
#define TSP_BASICHILLCLIMBING_H

#include <random>
#include "AbstractSolver.h"
#include "SequentialGreedy.h"
#include "./tool/Euclidean.h"

using namespace std;

class BasicHillClimbing: public AbstractSolver {
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
  void solve(Timer& timer, long long iteration) override;

  /**
   * Hill climbing is local search method.
   * Solution of local search is improved step by step.
   * So tour initializing is necessary.
   *
   * In this case, initialized as random tour.
   */
  void initializeTourAsRandom();

  /**
   * Hill climbing is local search method.
   * Solution of local search is improved step by step.
   * So tour initializing is necessary.
   *
   * In this case, initialized as greedy tour.
   *
   * @param timer
   */
  void initializeTourAsGreedy(Timer &timer);

  void initializeTourAsMST(Timer &timer);
};

#endif //TSP_BASICHILLCLIMBING_H
