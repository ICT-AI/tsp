#include "../header/Graph.h"

Graph::Graph(vector<vector<int>> &node_data) {
	this->nodes.reserve(node_data.size());

	for (auto single_data : node_data) {
		this->nodes.emplace_back(single_data[0], single_data[1], single_data[2]);
	}
}

vector<Node>& Graph::getNodes() {
	return this->nodes;
}
