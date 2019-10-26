#ifndef TSP_GREEDYSEARCHSA_H
#define TSP_GREEDYSEARCHSA_H

#include "AbstractLocalSearch.h"

class GreedySearchSA: public AbstractLocalSearch {
 protected:
  double tCurrent;

  double tEnd;

  double tCoolingRate;

  double tGreedyCount;

  int tAccept;

  vector<Node> mutationTour;

 protected:
  void solve(Timer& timer, long long iteration) override;

  void initializeAnnealingParams();

  double takeMutation();

  void vertexInsert();

  void blockInsert();

  void blockReverse();

  vector<Node> getMutationNeighbor();

  bool isAccept(double delta);

  double calculateAcceptanceProbability(double delta);

  double uniformRandom();
};

#endif //TSP_GREEDYSEARCHSA_H
