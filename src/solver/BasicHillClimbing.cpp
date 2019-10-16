#include "BasicHillClimbing.h"
#include "MSTGreedy.h"

void BasicHillClimbing::solve(Timer &timer, long long iteration) {
  // Initialize tour
  this->tour.assign(this->graph->getNodes().begin(), this->graph->getNodes().end());
  this->initializeAsMSTGreedy(timer);
//  this->initializeAsRandom();
//  this->initializeAsSequentialGreedy(timer);

  // Initialize cost
  this->cost = 0.;
  for (auto iter = this->tour.begin(); iter != this->tour.end() - 1; iter++) {
    this->cost += this->eucl->getDistance(*iter, *(iter + 1));
  }

  vector<Node> currTour(this->tour.begin(), this->tour.end());
  double currCost = this->cost;

  this->actualIteration = 1;

  vector<Node>::iterator t1, t2, t3, t4, best_t3;
  double old_cost1, old_cost2, new_cost1, new_cost2, curr_cost_benefit, best_cost_benefit;
  bool is_change;
  // start local search
  while (this->actualIteration < iteration) {
    // check if time is over
    if (timer.isOver()) {
      if (currCost < this->cost) {
        this->cost = currCost;
        this->tour.assign(currTour.begin(), currTour.end());
      }

      return;
    }

    is_change = false;

    for (t2 = currTour.begin(); t2 != currTour.end() - 1; t2++) {
      if (t2 == currTour.begin()) {
        old_cost1 = 0;
      } else {
        t1 = t2 - 1;
        old_cost1 = this->eucl->getDistance(*t1, *t2);
      }

      best_cost_benefit = 0;
      for (t3 = t2 + 1; t3 != currTour.end(); t3++) {
        if (t2 == currTour.begin()) {
          new_cost1 = 0;
        } else {
          new_cost1 = this->eucl->getDistance(*t1, *t3);
        }

        if (t3 == currTour.end() - 1) {
          old_cost2 = 0;
          new_cost2 = 0;
        } else {
          t4 = t3 + 1;
          old_cost2 = this->eucl->getDistance(*t3, *t4);
          new_cost2 = this->eucl->getDistance(*t2, *t4);
        }

        curr_cost_benefit = old_cost1 + old_cost2 - new_cost1 - new_cost2;
        // find best 2-opt case
        if (curr_cost_benefit > best_cost_benefit) {
          best_cost_benefit = curr_cost_benefit;
          best_t3 = t3;
        }
      }

      // tour is improved
      if (best_cost_benefit > 0.000000000001) {
        reverse(t2, best_t3 + 1);
        currCost -= best_cost_benefit;
        this->actualIteration++;
        is_change = true;
      }
    }

    // convergence to a local minima
    if (!is_change) {
      if (currCost < this->cost) {
        this->tour.assign(currTour.begin(), currTour.end());
        this->cost = currCost;
      }

//      currCost = this->kick(currTour);
      break;
    }
  }
}

double BasicHillClimbing::kick(vector<Node> &currTour) {
  random_device rn;
  mt19937_64 rnd(rn());

  int fraction = (int)currTour.size() / 10;

  uniform_int_distribution<int> range1(0, (int)currTour.size() - 4 * fraction);
  int c1 = range1(rnd);
  int c2 = c1 + 1;

  uniform_int_distribution<int> range2(c1 + 2, c1 + fraction);
  int d1 = range2(rnd);
  int d2 = d1 + 1;

  uniform_int_distribution<int> range3(d1 + 2, d1 + fraction);
  int c3 = range3(rnd);
  int c4 = c3 + 1;

  uniform_int_distribution<int> range4(c3 + 2, c3 + fraction);
  int d3 = range4(rnd);
  int d4 = d3 + 1;

  reverse(currTour.begin() + d2, currTour.begin() + d4);
  reverse(currTour.begin() + c2, currTour.begin() + c4);
  reverse(currTour.begin() + d2, currTour.begin() + d4);

  double cost =0.;
  for (auto iter = currTour.begin(); iter != currTour.end() - 1; iter++) {
    cost += this->eucl->getDistance(*iter, *(iter + 1));
  }

  return cost;
}
