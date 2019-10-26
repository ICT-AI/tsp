#ifndef TSP_EUCLIDEAN_H
#define TSP_EUCLIDEAN_H

#include <cmath>
#include <vector>
#include "../../model/Node.h"

using namespace std;

class Euclidean {
 public:
  /**
   * Calculate the euclidean distance between two points.
   *
   * @param x1
   * @param y1
   * @param x2
   * @param y2
   * @return
   */
  double getDistance(int x1, int y1, int x2, int y2);

  /**
   * Calculate the euclidean distance between two nodes.
   *
   * @param node1
   * @param node2
   * @return
   */
  double getDistance(Node &n1, Node &n2);

  /**
   * Calculate the euclidean squared distance between two points.
   *
   * @param x1
   * @param y1
   * @param x2
   * @param y2
   * @return
   */
  long long getSquaredDistance(int x1, int y1, int x2, int y2);

  /**
   * Calculate the euclidean squared distance between two nodes.
   *
   * @param node1
   * @param node2
   * @return
   */
  long long getSquaredDistance(Node &n1, Node &n2);

  double getTourCost(vector<Node> &tour);
};

#endif //TSP_EUCLIDEAN_H
