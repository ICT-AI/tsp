#include <iostream>
#include "./helper/FileHelper.h"
#include "./model/Graph.h"
#include "./solver/AbstractSolver.h"
#include "solver/SequentialGreedy.h"
#include "./helper/Timer.h"

void runTSP(const char *data_file_name, AbstractSolver &solver, int iteration, double time_limit){
  try {
    auto *fh = new FileHelper();
    auto nodes = fh->readDataFile(data_file_name);
    auto *graph = new Graph(nodes);
    auto *timer = new Timer(time_limit);

    solver.setGraph(graph);
    timer->start();
    solver.solve(iteration, *timer);
    double total_time = timer->getElapsedTime();

    // if tsp solved more than once
    if (solver.getActualIteration()) {
      cout << "tour: ";
      for (int node : solver.getTour()) {
        cout << node << " ";
      }
      cout << endl;

      cout << "cost: " << solver.getCost() << endl;

      cout << "time: " << total_time << endl;

      cout << "iteration: " << solver.getActualIteration() << endl;

      cout << "avg time: " << total_time / solver.getActualIteration() << endl;
    } else {
      cout << "Time over" << endl;
    }
  } catch (...) {
    cout << "ERROR OCCURRED" << endl;
  }
}

int main() {
  /************************************/
  /**** Set your test config here. ****/
  /************************************/
  const char* DATA_FILE = "xpr2308.txt";
  AbstractSolver *SOLVER = new SequentialGreedy();
  int ITERATION = INT_MAX;
  double TIME_LIMIT = 58.;

  runTSP(DATA_FILE, *SOLVER, ITERATION, TIME_LIMIT);

  return 0;
}