#include <stdlib.h>
#include <cstdlib>
#include <list>
#include "AbstractSolver.h"
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <cmath>
#include <set>
#include <sys/time.h>
#include <unistd.h>

#include<time.h>

#pragma comment(lib, "freeglut.lib")
#pragma comment(lib, "glew32.lib")

using namespace std;

vector<int> id;
vector<pair<double,double> > coord;

vector<pair<double,double> > nodes;//this is for draw path

class LKMatrix: public AbstractSolver {
 protected:
  /**
   * Solve TSP of current graph.
   * Use Hill Climbing (LK heuristic) algorithm(nearest neighbor).
   */
  void solve() override;

 public:
  int size;
  LKMatrix() = default;
  LKMatrix(Graph *g);
  LKMatrix(vector<pair<double, double> > &coords, vector<int> &ids);
  vector<int> getCurrentTour();
  double getCurrentTourDistance();
  void optimizeTour(); //solve()
  void printTour();
  void printTourIds();
  void indexForDraw();

private:
  //vector<int> tour ;
  vector<vector<int> > edgeFlags;
  vector<pair<double, double> > coords;
  vector<int> ids;
  void joinLocations(int i, int j);
  vector<vector<double>> edgeDistances;
  void LKMove(int tourStart);
  void reverse(int start, int end);
  bool isTour();
};