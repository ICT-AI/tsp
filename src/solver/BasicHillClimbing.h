#ifndef TSP_BASICHILLCLIMBING_H
#define TSP_BASICHILLCLIMBING_H

#include "AbstractLocalSearch.h"

using namespace std;

class BasicHillClimbing: public AbstractLocalSearch {
 protected:
  /**
   * Solve TSP of current graph.
   * Use basic greedy algorithm(nearest neighbor).
   */
  void solve(Timer &timer, long long iteration) override;

  double kick(vector<Node> &currTour);
};

#endif //TSP_BASICHILLCLIMBING_H
