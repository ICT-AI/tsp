#include "BasicSA.h"
#include "./tool/NeighbourManager.h"
#include <iostream>

void BasicSA::solve(Timer &timer, long long iteration) {
  // initialize tour
  if (this->tour.empty()) {
    this->initializeAsRandom();
    //  this->initializeAsMSTGreedy(timer);
  }

  // initialize cost
  this->cost = 0.;
  for (auto iter = this->tour.begin(); iter != this->tour.end() - 1; iter++) {
    this->cost += this->eucl->getDistance(*iter, *(iter + 1));
  }

  this->initializeTemperature();

  this->actualIteration = 1;

  vector<Node> currTour(this->tour);
  double currCost = this->cost;
  vector<Node> semiOptTour(this->tour);
  double semiOptCost = this->cost;
  double tempStageCost = this->cost;
//  auto neighbours = new NeighbourManager();
  vector<Node>::iterator t1, t2, t3, t4;
  double old_cost1, old_cost2, new_cost1, new_cost2, delta;
  pair<int, int> neighbour;

  int accept_count = 0;

  // start local search
  while (this->actualIteration < iteration) {
    random_device rn;
    mt19937_64 rnd(rn());
    uniform_int_distribution<int> range1(0, currTour.size() - 2);

    // pick random neighbour
//    neighbours->initializeAsRandom(currTour.size());
    while (true) {
      // check if time is over
//      if (timer.isOver()) {
//        if (currCost < this->cost) {
//          this->cost = currCost;
//          this->tour.assign(currTour.begin(), currTour.end());
//        }
//
//        return;
//      }

      if (timer.getRemainingTime() < 7. || this->temperature < 0.0000000001) {
        AbstractLocalSearch *hill_climber = new BasicHillClimbing();
        auto graph = new Graph();
        graph->setNodes(currTour);
        hill_climber->setGraphAndTour(graph);
        hill_climber->solve(timer, LL_MAX);

        this->tour.assign(hill_climber->getTour().begin(), hill_climber->getTour().end());
        this->cost = 0.;
        for (auto iter = this->tour.begin(); iter != this->tour.end() - 1; iter++) {
          this->cost += this->eucl->getDistance(*iter, *(iter + 1));
        }

        return;
      }

//      neighbour = neighbours->popNeighbour();

      int first = range1(rnd);
      uniform_int_distribution<int> range2(first + 1, currTour.size() - 1);
      int second = range2(rnd);
      t2 = currTour.begin() + first;
      t3 = currTour.begin() + second;

//      t2 = currTour.begin() + neighbour.first;
//      t3 = currTour.begin() + neighbour.second;
      t1 = t2 - 1;
      t4 = t3 + 1;

      if (t2 == currTour.begin()) {
        old_cost1 = 0.;
        new_cost1 = 0.;
      } else {
        old_cost1 = this->eucl->getDistance(*t1, *t2);
        new_cost1 = this->eucl->getDistance(*t1, *t3);
      }

      if (t3 == currTour.end() - 1) {
        old_cost2 = 0.;
        new_cost2 = 0.;
      } else {
        old_cost2 = this->eucl->getDistance(*t3, *t4);
        new_cost2 = this->eucl->getDistance(*t2, *t4);
      }

      delta = new_cost1 + new_cost2 - old_cost1 - old_cost2;
      if (this->isAccept(delta)) {
        reverse(t2, t3 + 1);
        currCost += delta;
        this->actualIteration++;
        accept_count++;

        if (currCost < semiOptCost) {
          semiOptCost = currCost;
          semiOptTour.assign(currTour.begin(), currTour.end());
        }

        if (accept_count == 395) {
          currCost = semiOptCost;
          currTour.assign(semiOptTour.begin(), semiOptTour.end());

          this->cooling(tempStageCost, semiOptCost - tempStageCost);
          tempStageCost = semiOptCost;
          accept_count = 0;
          semiOptCost = LL_MAX;

          cout << this->temperature << endl;
          cout << currCost << endl << endl;
        }
      }
    }
  }
}

void BasicSA::initializeTemperature() {
  double mean_cost = this->cost / this->getTour().size();

  this->temperature = 10 * mean_cost;
}

void BasicSA::cooling(double energy, double delta) {
  double cooling_rate = 0.03;
  this->temperature *= (1 - cooling_rate);

//  double cooling_rate = (-3. * delta) / energy;
//  this->temperature *= (1 - cooling_rate);

//  if (delta < 0.) {
//    double cooling_rate = (-3 * delta) / energy;
//    this->temperature *= (1 - cooling_rate);
//  }
}

bool BasicSA::isAccept(double delta) {
  if (delta < 0.) {
    return true;
  }

  double accept_prob = this->calculateAcceptanceProbability(delta);
  if (accept_prob >= this->uniformRandom()) {
    return true;
  }

  return false;
}

double BasicSA::calculateAcceptanceProbability(double delta) {
  double exponent = delta / this->temperature;
//  double probability = 1 / (1 + pow(M_E, exponent));
  double probability = pow(M_E, -1 * exponent);
//  cout << probability << endl;

  return probability;
}

double BasicSA::uniformRandom() {
  random_device rd;
  mt19937_64 gen(rd());
  uniform_real_distribution<> dis(0.0, 1.0);

  return dis(gen);
}