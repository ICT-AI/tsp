#ifndef TSP_GRAPH_H
#define TSP_GRAPH_H

#include <vector>
#include <utility>
#include <cmath>

using namespace std;

class Graph {
 private:
  /**
   * Node set of the graph.
   * Each node format: (x_coord, y_coord)
   */
  vector<pair<int ,int>> nodes;

 public:
  /**
   * Create Graph object from the node set.
   *
   * @param nodes
   */
  Graph(vector<pair<int, int>> nodes);

  /**
   * Return the node set of this graph.
   *
   * @return
   */
  vector<pair<int, int>> getNodes();

  /**
   * Calculate the euclidean distance between two nodes.
   *
   * @param node1   node index
   * @param node2   node index
   * @return
   */
  float getDistance(int node1, int node2);
};

#endif //TSP_GRAPH_H
