#include "Graph.h"

Graph::Graph(vector<pair<int, int>> nodes) {
  this->nodes = nodes;
}

vector<pair<int, int>> Graph::getNodes() {
  return this->nodes;
}

float Graph::getDistance(int node1, int node2) {
  auto node1_coord = this->nodes[node1];
  auto node2_coord = this->nodes[node2];

  float dx = node1_coord.first - node2_coord.first;
  float dy = node1_coord.second - node2_coord.second;

  return sqrt(dx * dx + dy * dy);
}