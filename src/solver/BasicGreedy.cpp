#include "BasicGreedy.h"

void BasicGreedy::solve() {
  list<Node> unvisited_nodes(this->graph->getNodes().begin(), this->graph->getNodes().end());
  unvisited_nodes.sort();

  list<Node>::iterator iter, nn;
  float total_cost = 0.0;
  this->tour.reserve(this->graph->getNodes().size());

  // start the node which is nearest from origin.
  Node curr_node = unvisited_nodes.front();
  unvisited_nodes.erase(unvisited_nodes.begin());
  this->tour.push_back(curr_node.index);

  // until visit all nodes
  long long min_squared_distance, x_squared_distance, curr_squared_distance;
  while (!unvisited_nodes.empty()) {
    min_squared_distance = LONG_LONG_MAX;
    for (iter = unvisited_nodes.begin(); iter != unvisited_nodes.end(); iter++) {
      // for early stop
      x_squared_distance = this->eucl->getSquaredDistance(curr_node.x, 0, (*iter).x, 0);
      if (x_squared_distance > min_squared_distance) {
        break;
      }

      // update nearest node
      curr_squared_distance = this->eucl->getSquaredDistance(curr_node, *iter);
      if (curr_squared_distance < min_squared_distance) {
        min_squared_distance = curr_squared_distance;
        nn = iter;
      }
    }

    curr_node = *nn;
    unvisited_nodes.erase(nn);
    total_cost += sqrt(min_squared_distance);
    this->tour.push_back(curr_node.index);
  }

  this->cost = (int)total_cost;
}