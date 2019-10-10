#include "BasicHillClimbingWithSA.h"
double temperature=1000;//distance between x coords of first/final node. 일단 간단하게 6880 데이터의 x차이를 대입

//Carculating Probabliity
double AnnealingProb(double deltaCost){//확률계산
  double annealProb=deltaCost/(2*temperature)+0.07;//반환할것
  if(deltaCost>=0){//여기서 온도는 기존공식과는 다르게 직선이 꺾이는 점의 x좌표로 잡았다. 사용된 확률 그래프는'_/-'처럼 생김
    return min(1.0, annealProb);
  }else if(deltaCost<0){
    return max(0.0,annealProb);
  }
  return annealProb;
}

//Random pick by value.
double MakeRandNum(vector<double> vecProb) {
    random_device rd;
    mt19937 gen(rd());
 
    discrete_distribution<double> d{ vecProb.cbegin(), vecProb.cend() };
    /*
    auto it = vecProb.cbegin();
    std::discrete_distribution<> d(vecProb.size(), 0, 0, [&](T x)->T {
        auto val = *it;
        it++;
        return val;
    });
    */
 
    return d(gen);
}

void BasicHillClimbingWithSA::solve(Timer &timer, long long iteration) {
  // Initialize tour
  this->initializeTourAsGreedy(timer);
//  this->initializeTourAsRandom();

  // Initialize cost
  this->cost = 0.;
  for (auto iter = this->tour.begin(); iter != this->tour.end() - 1; iter++) {
    this->cost += this->eucl->getDistance(*iter, *(iter + 1));
  }

  this->actualIteration = 1;

  vector<Node>::iterator t1, t2, t3, t4, best_t3;
  double old_cost1, old_cost2, new_cost1, new_cost2, curr_cost_benefit, best_cost_benefit;
  bool is_change;
  // start local search
  while (this->actualIteration < iteration) {
    // check if time is over
    if (timer.isOver()) {
      return;
    }

    is_change = false;

    for (t2 = this->tour.begin(); t2 != this->tour.end() - 1; t2++) {
      if (t2 == this->tour.begin()) {
        old_cost1 = 0;
      } else {
        t1 = t2 - 1;
        old_cost1 = this->eucl->getDistance(*t1, *t2);
      }

      vector<double> cost_prob; //For Carculate Probability-jekyun
      best_cost_benefit = 0;
      for (t3 = t2 + 1; t3 != this->tour.end(); t3++) {
        if (t2 == this->tour.begin()) {
          new_cost1 = 0;
        } else {
          new_cost1 = this->eucl->getDistance(*t1, *t3);
        }

        if (t3 == this->tour.end() - 1) {
          old_cost2 = 0;
          new_cost2 = 0;
        } else {
          t4 = t3 + 1;
          old_cost2 = this->eucl->getDistance(*t3, *t4);
          new_cost2 = this->eucl->getDistance(*t2, *t4);
        }

        curr_cost_benefit = old_cost1 + old_cost2 - new_cost1 - new_cost2;
        cost_prob.push_back(AnnealingProb(curr_cost_benefit)); //Collect cost benefits difference by t3-jekyun
        
        /***Non-SA code -jekyun
        // find best 2-opt case
        if (curr_cost_benefit > best_cost_benefit) {
          best_cost_benefit = curr_cost_benefit;
          best_t3 = t3;
        }
        ***/
      }

      // Calculate probability of probability. -jekyun 
      int finding=0;
      finding = find(cost_prob.begin(), cost_prob.end(), best_cost_benefit=MakeRandNum(cost_prob)) - cost_prob.begin();
      reverse(t2, t2+finding+1);
      this->cost -= best_cost_benefit;
      this->actualIteration++;
      is_change = true;


      /***Non-SA code -jekyun
      // tour is improved
      if (best_cost_benefit > 0.000000000001) {
        reverse(t2, best_t3 + 1);
        this->cost -= best_cost_benefit;
        this->actualIteration++;
        is_change = true;
      }***/
    }

    // convergence to a local minima
    if (!is_change) {
      break;
    }
  }
}

void BasicHillClimbingWithSA::initializeTourAsRandom() {
  this->tour.assign(this->graph->getNodes().begin(), this->graph->getNodes().end());
  unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  shuffle(this->tour.begin(), this->tour.end(), default_random_engine(seed)); // uniform random shuffle
}

void BasicHillClimbingWithSA::initializeTourAsGreedy(Timer &timer) {
  AbstractSolver *greedySolver = new SequentialGreedy();
  auto *graph = new Graph();
  graph->setNodes(this->graph->getNodes());

  greedySolver->setGraph(graph);
  greedySolver->solve(timer, 2);
  this->tour.assign(greedySolver->getTour().begin(), greedySolver->getTour().end());
}