#ifndef TSP_BASICSA_H
#define TSP_BASICSA_H

#include "AbstractLocalSearch.h"
#include "BasicHillClimbing.h"

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

  void cooling(double energy, double delta);

  bool isAccept(double delta);

  double calculateAcceptanceProbability(double delta);

  double uniformRandom();
};

#endif //TSP_BASICSA_H
