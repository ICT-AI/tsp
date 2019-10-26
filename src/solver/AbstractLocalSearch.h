#ifndef TSP_ABSTRACTLOCALSEARCH_H
#define TSP_ABSTRACTLOCALSEARCH_H

#include <random>
#include "AbstractSolver.h"
#include "AbstractGreedy.h"
#include "SequentialGreedy.h"
#include "MSTGreedy.h"

class AbstractLocalSearch: public AbstractSolver {
 protected:
  /**
   * Solution of local search is improved step by step.
   * So tour initializing is necessary.
   *
   * In this case, initialize tour as random.
   */
  void initializeAsRandom();

  /**
   * Initialize tour as sequential greedy algorithm.
   *
   * @param timer
   */
  void initializeAsSequentialGreedy(Timer &timer);

  /**
   * Initialize tour as MST greedy algorithm.
   *
   * @param timer
   */
  void initializeAsMSTGreedy(Timer &timer);

 public:
  /**
   * Set graph and initial tour.
   * If you want to start with specific tour,
   * use this method rather than `setGraph`.
   *
   * @param g
   */
  void setGraphAndTour(Graph *g);
};

#endif //TSP_ABSTRACTLOCALSEARCH_H
