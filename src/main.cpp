#include <iostream>
#include "./helper/FileHelper.h"
#include "./model/Graph.h"
#include "./solver/AbstractSolver.h"
#include "./solver/SequentialGreedy.h"
#include "./solver/BasicHillClimbing.h"
#include "./solver/MapSearchGreedy.h"
#include "./solver/MSTGreedy.h"
#include "./helper/Timer.h"
#include "./solver/BasicSA.h"
#include "./solver/GreedySearchSA.h"

void runTSP(const char *data_file_name, AbstractSolver &solver, double time_limit, long long iteration){
  try {
    auto *fh = new FileHelper();
    auto nodes = fh->readDataFile(data_file_name);
    auto *graph = new Graph(nodes);
    auto *timer = new Timer(time_limit);

    solver.setGraph(graph);
    timer->start();
    if (iteration == -1) {
      solver.solve(*timer);
    } else {
      solver.solve(*timer, iteration);
    }
    double total_time = timer->getElapsedTime();

    // wrong tour
    if (!solver.verifyTour()) {
      throw logic_error("ERROR: Tour is wrong");
    }

    // tsp not solved
    if (!solver.getActualIteration()) {
      throw logic_error("ERROR: Time over");
    }

    // output result as file
//    string output_file_name(data_file_name);
//    string delimiter(".");
//    output_file_name = output_file_name.substr(0, output_file_name.find(delimiter));
//    output_file_name.append(".result.txt");
//    fh->writeTourAsFile(output_file_name.c_str(), solver.getTour());

    cout << "tour: ";
    for (auto node : solver.getTour()) {
      cout << node.index << " ";
    }
    cout << endl;
    cout << "cost: " << solver.getCost() << endl;
    cout << "time: " << total_time << endl;
    cout << "iteration: " << solver.getActualIteration() << endl;
    cout << "avg time: " << total_time / solver.getActualIteration() << endl;
  } catch (exception &e) {
    cerr << e.what() << endl;
  }
}

int main() {
  /************************************/
  /**** Set your test config here. ****/
  /************************************/
  const char* DATA_FILE = "xmc10150.tsp.txt";
  AbstractSolver *SOLVER = new BasicSA();
  double TIME_LIMIT = 179.;
  long long ITERATION = LL_MAX;

  runTSP(DATA_FILE, *SOLVER, TIME_LIMIT, ITERATION);

  return 0;
}
