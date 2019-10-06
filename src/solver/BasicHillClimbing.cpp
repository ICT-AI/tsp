#include "BasicHillClimbing.h"

void BasicHillClimbing::solve(Timer &timer, long long iteration) {
  // Initialize random tour
  this->tour.assign(this->graph->getNodes().begin(), this->graph->getNodes().end());
  unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  shuffle(this->tour.begin(), this->tour.end(), default_random_engine(seed));

  // Initialize cost
  this->cost = 0.0;
  for (auto iter = this->tour.begin(); iter != this->tour.end() - 1; iter++) {
    this->cost += this->eucl->getDistance(*iter, *(iter + 1));
  }

  this->actualIteration = 1;

  vector<Node>::iterator t1, t2, t3, t4, best_t3;
  float old_cost1, old_cost2, new_cost1, new_cost2, curr_cost_benefit, best_cost_benefit;
  bool is_change;
  // start local search
  while (this->actualIteration < iteration) {
    // check if time is over
    if (timer.isOver()) {
      return;
    }

    is_change = false;

    for (t2 = this->tour.begin(); t2 != this->tour.end() - 1; t2++) {
      t1 = t2 - 1;

      if (t2 == this->tour.begin()) {
        old_cost1 = 0;
      } else {
        old_cost1 = this->eucl->getDistance(*t1, *t2);
      }

      best_cost_benefit = 0;
      for (t3 = t2 + 1; t3 != this->tour.end(); t3++) {
        t4 = t3 + 1;

        if (t2 == this->tour.begin()) {
          new_cost1 = 0;
        } else {
          new_cost1 = this->eucl->getDistance(*t1, *t3);
        }

        if (t3 == this->tour.end() - 1) {
          old_cost2 = 0;
          new_cost2 = 0;
        } else {
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
      if (best_cost_benefit > 0) {
        reverse(t2, best_t3 + 1);
        this->cost -= best_cost_benefit;
        this->actualIteration++;
        is_change = true;
      }
    }

    // convergence to a local minima
    if (!is_change) {
      break;
    }
  }
}
