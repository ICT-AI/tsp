#ifndef TSP_BASICSA_H
#define TSP_BASICSA_H

#include "AbstractLocalSearch.h"

class BasicSA: public AbstractLocalSearch {
 protected:
  double temperature;

 protected:
  /**
   * Solve TSP of current graph.
   * Use basic greedy algorithm(nearest neighbor).
   */
  void solve(Timer& timer, long long iteration) override;

  void initializeTemperature();

  void updateTemperature();

  double calculateAcceptanceProbability(double cost_diff);
};

#endif //TSP_BASICSA_H
