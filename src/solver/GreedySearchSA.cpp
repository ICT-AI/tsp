#include "GreedySearchSA.h"
#include <iostream>

void GreedySearchSA::solve(Timer &timer, long long iteration) {
  // initialize tour
  if (this->tour.empty()) {
    this->initializeAsRandom();
  }

  this->initializeAnnealingParams();

  this->actualIteration++;

  double mutationDelta;
  int currentGreedyCount = 0;
  double bestGreedyCost = INT_MAX, currentGreedyCost;
  vector<Node> bestGreedyTour, currentGreedyTour;
  while (this->tCurrent >= this->tEnd) {
    if (timer.isOver()) {
      return;
    }
    mutationDelta = this->takeMutation();

    if (mutationDelta <= 0) {
      this->tour.assign(this->mutationTour.begin(), this->mutationTour.end());
      this->cost = this->eucl->getTourCost(this->tour);

      this->tCurrent *= this->tCoolingRate;
      currentGreedyCount = 0;
      bestGreedyCost = INT_MAX;
      bestGreedyTour.clear();
    } else {
      currentGreedyCount++;

      currentGreedyTour = this->getMutationNeighbor();
      currentGreedyCost = this->eucl->getTourCost(currentGreedyTour);
      if (currentGreedyCost < bestGreedyCost) {
        bestGreedyCost = currentGreedyCost;
        bestGreedyTour.assign(currentGreedyTour.begin(), currentGreedyTour.end());
      }

      if (currentGreedyCount >= this->tGreedyCount) {
        if (this->isAccept(bestGreedyCost - this->eucl->getTourCost(this->mutationTour))) {
          this->tour.assign(bestGreedyTour.begin(), bestGreedyTour.end());
          this->cost = bestGreedyCost;
        }

        this->tCurrent *= this->tCoolingRate;
        currentGreedyCount = 0;
        bestGreedyCost = INT_MAX;
        bestGreedyTour.clear();

        cout << this->cost << endl;
        cout << this->tCurrent << endl;
      }
    }
  }
}

void GreedySearchSA::initializeAnnealingParams() {
  double alpha = 1.2 * 10;
  double beta = 0.001;
  double n = this->graph->getNodes().size();

  this->tCurrent = 1000.;
  this->tEnd = 0.0025;
  this->tCoolingRate = (alpha * sqrt(n) - 1.) / (alpha * sqrt(n));
  this->tGreedyCount = beta * n;
  this->tAccept = (int)n / 10;
}

double GreedySearchSA::takeMutation() {
  this->mutationTour.assign(this->tour.begin(), this->tour.end());

  random_device rn;
  mt19937_64 rnd(rn());
  uniform_int_distribution<int> range(0, 2);

  int selectedMutation = range(rnd);
  switch (selectedMutation) {
    case 0:
//      this->vertexInsert();
      this->blockReverse();
      break;

    case 1:
//      this->blockInsert();
      this->blockReverse();
      break;

    case 2:
      this->blockReverse();
      break;

    default:
      ;
  }

  double delta = this->eucl->getTourCost(this->mutationTour) - this->cost;

  return delta;
}

void GreedySearchSA::vertexInsert() {
  random_device rn;
  mt19937_64 rnd(rn());
  int t1, t2;

  uniform_int_distribution<int> range1(0, this->mutationTour.size() - 2);
  t1 = range1(rnd);
  uniform_int_distribution<int> range2(t1 + 1, this->mutationTour.size() - 1);
  t2 = range2(rnd);

  Node t2Node(this->mutationTour[t2]);
  this->mutationTour.erase(this->mutationTour.begin() + t2);
  this->mutationTour.insert(this->mutationTour.begin() + t1, t2Node);
}

void GreedySearchSA::blockInsert() {
  random_device rn;
  mt19937_64 rnd(rn());
  int t1, t2;

  uniform_int_distribution<int> range1(0, this->mutationTour.size() - 2);
  t1 = range1(rnd);
  uniform_int_distribution<int> range2(t1 + 1, (this->mutationTour.size() - t1) / 2);
  t2 = range2(rnd);

  int blockLength = t2 - t1;
  for (int i = 0; i < blockLength; i++) {
    iter_swap(this->mutationTour.begin() + t1 + i, this->mutationTour.begin() + t1 + i + blockLength);
  }
}

void GreedySearchSA::blockReverse() {
  random_device rn;
  mt19937_64 rnd(rn());
  int t1, t2;

  uniform_int_distribution<int> range1(0, this->mutationTour.size() - 2);
  t1 = range1(rnd);
  uniform_int_distribution<int> range2(t1 + 1, this->mutationTour.size() - 1);
  t2 = range2(rnd);

  reverse(this->mutationTour.begin() + t1, this->mutationTour.begin() + t2 + 1);
}

vector<Node> GreedySearchSA::getMutationNeighbor() {
  random_device rn;
  mt19937_64 rnd(rn());
  int t1, t2;

  uniform_int_distribution<int> range1(0, this->mutationTour.size() - 2);
  t1 = range1(rnd);
  uniform_int_distribution<int> range2(t1 + 1, this->mutationTour.size() - 1);
  t2 = range2(rnd);

  vector<Node> neighbor(this->mutationTour);
  reverse(neighbor.begin() + t1, neighbor.begin() + t2);

  return neighbor;
}

bool GreedySearchSA::isAccept(double delta) {
  double accept_prob = this->calculateAcceptanceProbability(delta);
  if (accept_prob > this->uniformRandom()) {
    return true;
  }

  return false;
}

double GreedySearchSA::calculateAcceptanceProbability(double delta) {
  double exponent = (delta / this->tCurrent) * (10. * (this->graph->getNodes().size() / 28387.));
  double probability = pow(M_E, -1 * exponent);

  return probability;
}

double GreedySearchSA::uniformRandom() {
  random_device rd;
  mt19937_64 gen(rd());
  uniform_real_distribution<> dis(0.0, 1.0);

  return dis(gen);
}