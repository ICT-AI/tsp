#include <iostream>
#include "./helper/FileHelper.h"
#include "./model/Graph.h"
#include "./solver/AbstractSolver.h"
#include "./solver/BasicGreedy.h"

void runTSP(const char *data_file_name, AbstractSolver *solver){
  try {
    auto *fh = new FileHelper();
    auto nodes = fh->readDataFile(data_file_name);
    auto *graph = new Graph(nodes);

    solver->setGraph(graph);
    solver->solveAndMeasureTime();

    cout << "tour: ";
    for (int node : solver->getTour()) {
      cout << node << " ";
    }
    cout << endl;

    cout << "cost: " << solver->getCost() << endl;

    cout << "time: " << solver->getElapsedTime() << endl;
  } catch (...) {
    cout << "ERROR OCCURRED" << endl;
  }
}

int main() {
  runTSP("xql662.txt", new BasicGreedy());

  return 0;
}