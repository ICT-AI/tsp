#ifndef TSP_GRAPH_H
#define TSP_GRAPH_H

#include <vector>
#include <utility>
#include <cmath>
#include "Node.h"

using namespace std;

class Graph {
private:
	/**
	 * Node set of the graph.
	 */
	vector<Node> nodes;

public:
	/**
	 * Create Graph object with node data.
	 *
	 * @param node_data
	 */
	Graph(vector<vector<int>> &node_data);

	/**
	 * Return the node set of this graph.
	 *
	 * @return
	 */
	vector<Node>& getNodes();
};

#endif //TSP_GRAPH_H
