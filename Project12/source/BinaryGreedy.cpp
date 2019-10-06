#include "../header/BinaryGreedy.h"

void setRange(list<Node>& uvn, list<Node>::iterator &_lower, const list<Node>::iterator& cur, list<Node>::iterator& _upper, int _range) {
	list<Node>::iterator lower, upper;
	int range = 0;
	lower = cur;
	upper = cur;
	int prevX = (*cur).x;
	
	while (1) {
		if (lower == uvn.begin() || range == _range) {
			break;
		}
		if (prevX != (*lower).x) {
			range++;
			prevX = (*lower).x;
			continue;
		}
		lower--;
	}
	if (lower != uvn.begin()) {
		lower++;
	}
	prevX = (*cur).x;
	range = 0;

	while (1) {
		if (upper == (--uvn.end()) || range == _range) {
			break;
		}
		if (prevX != (*upper).x) {
			range++;
			prevX = (*upper).x;
			continue;
		}
		upper++;
	}
	if (upper == (--uvn.end()))
		upper = uvn.end();

	_lower = lower;
	_upper = upper;
}

void BinaryGreedy::solve(int iteration, Timer& timer) {
	sort(this->graph->getNodes().begin(), this->graph->getNodes().end()); // sort graph node list
	deque<Node> start_node_list = this->getStartIndexList();  // start node index list for iterative solving

	// until specified iteration or entire node size
	for (int i = 0; i < min(iteration, (int)this->graph->getNodes().size()); i++) {
		// initialize unvisited nodes, cost, tour
		list<Node> unvisited_nodes(this->graph->getNodes().begin(), this->graph->getNodes().end());
		float cost = 0.0;
		vector<Node> tour;
		tour.reserve(this->graph->getNodes().size());
		// set the starting node
		Node start_node = start_node_list.front();
		start_node_list.pop_front();

		list<Node>::iterator cur = lower_bound(unvisited_nodes.begin(), unvisited_nodes.end(), start_node);
		list<Node>::iterator upper,lower, nearest_node;
		long long curr_squared_distance,min_squared_distance;

		while (!unvisited_nodes.empty()) {
			if (timer.isOver()) {
				return;
			}
			Node curr_node = *cur;
			setRange(unvisited_nodes, lower, cur, upper, 10);
			min_squared_distance = INT_MAX;

			list<Node>::iterator iter;

			for (iter = lower; iter != upper; iter++) {
				curr_squared_distance = this->eucl->getSquaredDistance(curr_node, *iter);
				if (curr_squared_distance < min_squared_distance && (*iter).index != curr_node.index) {
					min_squared_distance = curr_squared_distance;
					nearest_node = iter;
				}
			}
			if (min_squared_distance == INT_MAX) {
				tour.push_back(*cur);
				unvisited_nodes.erase(cur);
				continue;
			}
			tour.push_back(*cur);
			unvisited_nodes.erase(cur);
			cost += sqrt(min_squared_distance); // add cost
			cur = nearest_node;	
		}
		if (cost < this->cost) {
			this->cost = cost;
			this->tour.assign(tour.begin(), tour.end());
		}
		this->actualIteration++;  // increase solve count

	}

}

list<list<Node>> BinaryGreedy::makeNodeList() {
	list<list<Node>> node_tree;
	auto nodes = this->graph->getNodes();
	int num = nodes.size();
	list<Node> tlist = { nodes[0] };
	node_tree.push_back(tlist);
	for (int i = 1; i < num; i++) {
		if (nodes[i].x == node_tree.back().back().x) {
			node_tree.back().push_back(nodes[i]);
		}
		else {
			tlist = { nodes[i] };
			node_tree.push_back(tlist);
		}
	}
	return node_tree;

 }
deque<Node> BinaryGreedy::getStartIndexList() {
	deque<Node> start_index_list;
	// copy from original node list
	for (auto node : this->graph->getNodes()) {
		start_index_list.push_back(node);
	}

	// pop first and last index which are should be run
	Node front = start_index_list.front();
	Node back = start_index_list.back();
	start_index_list.pop_front();
	start_index_list.pop_back();

	// shuffle
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	shuffle(start_index_list.begin(), start_index_list.end(), default_random_engine(seed));

	// push first and last index to front
	start_index_list.push_front(back);
	start_index_list.push_front(front);

	return start_index_list;
}