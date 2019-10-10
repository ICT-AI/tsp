#include "MapSearchGreedy.h"

const int MAX = 10000;


void MapSearchGreedy::solve(Timer &timer, long long iteration) {
	sort(this->graph->getNodes().begin(), this->graph->getNodes().end()); // sort graph node list
	deque<Node> start_node_list = this->getStartIndexList();  // start node index list for iterative solving
	map<int, map<int, Node>> nodeMap;
	vector<Node> nodes = this->graph->getNodes();
	vector<Node>::iterator iter;
	for (iter = nodes.begin(); iter != nodes.end(); ++iter) {
		nodeMap[iter->x][iter->y] = *iter;
	}// create node map

	for (int i = 0; i < min(iteration, (long long)this->graph->getNodes().size()); i++) {
		cout << timer.getElapsedTime() << endl;
		if (timer.isOver()) {
			cout << "over" << endl;
			return;
		}

		map<int, map<int, Node>> copyMap = nodeMap;
		float cost = 0.0;
		vector<Node> tour;
		tour.reserve(this->graph->getNodes().size());
		start_node_list.pop_front();
		Node curr_node = start_node_list.front();
		start_node_list.pop_front();
		map<int, map<int, Node>>::iterator xit, temp_x_it;
		map<int, Node>::iterator yit, temp_y_it, nearest_node;

		while (!copyMap.empty()) {

			//find curr_node iterator
			xit = copyMap.find(curr_node.x);
			yit = xit->second.find(curr_node.y);

			// find  minimal different value in current x & save nearest node
			int min_differ_y = MAX;
			temp_y_it = yit; temp_y_it++; //search up
			if (temp_y_it != xit->second.end()) {
				min_differ_y = temp_y_it->second.y - curr_node.y;
				nearest_node = temp_y_it;
			}
			temp_y_it = yit; temp_y_it--; //search down
			if (temp_y_it != xit->second.end()) {
				if (min_differ_y >= curr_node.y - temp_y_it->second.y) {
					min_differ_y = curr_node.y - temp_y_it->second.y;
					nearest_node = temp_y_it;
				}
			}

			//search in different x value
			int differ_x = MAX;
			temp_x_it = xit; temp_x_it++;
			if (temp_x_it != copyMap.end()) {
				differ_x = temp_x_it->first - xit->first;
			}
			temp_x_it = xit; temp_x_it--;
			if (temp_x_it != copyMap.end()) {
				if (xit->first - temp_x_it->first < differ_x) {
					differ_x = xit->first - temp_x_it->first;
				}

			}

			if (differ_x == MAX && min_differ_y == MAX) {
				//no node except current node ; 
				tour.push_back(curr_node);  // update tour
				xit->second.erase(yit);
				if (xit->second.size() == 0) {
					copyMap.erase(xit);
				}
			}
			else if (differ_x == MAX) {
				//no node except current x 
				tour.push_back(curr_node);  // update tour
				xit->second.erase(yit);
				if (xit->second.size() == 0) {
					copyMap.erase(xit);
				}
				cost += min_differ_y; // add cost
				curr_node = nearest_node->second;  // move to new node
			}
			else {

				temp_x_it = xit; temp_x_it++;
				differ_x; min_differ_y;

				long long min_squared_distance = min_differ_y * min_differ_y;// if no nodes in same x then MAX*MAX
				long long curr_squared_distance;

				//search up 
				temp_x_it = xit; temp_x_it++;
				while (temp_x_it != copyMap.end() && (temp_x_it->first - xit->first)*(temp_x_it->first - xit->first) <= min_squared_distance) {
					//find y value of curr_node in temp_x_it
					temp_y_it = temp_x_it->second.find(curr_node.y);

					//if no value then temp_y_it is end() 
					if (temp_y_it == temp_x_it->second.end()) {
						Node tnode;
						temp_x_it->second[curr_node.y] = tnode;
						temp_y_it = temp_x_it->second.find(curr_node.y); //insert temp Node and find iterator 
						map<int, Node>::iterator y_plus_it, y_minus_it;
						
						y_minus_it = temp_y_it; y_minus_it--;
						y_plus_it = temp_x_it->second.erase(temp_y_it); //find up down iterator and erase temp node

															// find smaller value in up&down
						if (y_plus_it == temp_x_it->second.end()) {
							temp_y_it = y_minus_it;
						}
						else if (y_minus_it == temp_x_it->second.end()) {
							temp_y_it = y_plus_it;
						}
						else {
							if (y_plus_it->first - curr_node.y >= curr_node.y - y_minus_it->first) {
								temp_y_it = y_minus_it;
							}
							else {
								temp_y_it = y_plus_it;
							}
						}
						//measure distance and update min_sqr, nearest_node
						curr_squared_distance = this->eucl->getSquaredDistance(curr_node, temp_y_it->second);
						if (curr_squared_distance < min_squared_distance) {
							min_squared_distance = curr_squared_distance;
							nearest_node = temp_y_it;
						}
					}
					// if value exist then measure distance and update min_sqr, nearest_node
					else {
						curr_squared_distance = this->eucl->getSquaredDistance(curr_node, temp_y_it->second);
						if (curr_squared_distance < min_squared_distance) {
							min_squared_distance = curr_squared_distance;
							nearest_node = temp_y_it;
						}
					}
					temp_x_it++;
				}

				//search down 
				temp_x_it = xit; temp_x_it--;
				while (temp_x_it != copyMap.end() && (xit->first - temp_x_it->first)* (xit->first - temp_x_it->first) <= min_squared_distance) {
					temp_y_it = temp_x_it->second.find(curr_node.y);
					if (temp_y_it == temp_x_it->second.end()) {
						Node tnode;
						temp_x_it->second[curr_node.y] = tnode;
						temp_y_it = temp_x_it->second.find(curr_node.y); 
						map<int, Node>::iterator y_plus_it, y_minus_it;
						y_minus_it = temp_y_it; y_minus_it--;
						y_plus_it = temp_x_it->second.erase(temp_y_it);

						if (y_plus_it == temp_x_it->second.end()) {
							temp_y_it = y_minus_it;
						}
						else if (y_minus_it == temp_x_it->second.end()) {
							temp_y_it = y_plus_it;
						}
						else {
							if (y_plus_it->first - curr_node.y >= curr_node.y - y_minus_it->first) {
								temp_y_it = y_minus_it;
							}
							else {
								temp_y_it = y_plus_it;
							}
						}
						curr_squared_distance = this->eucl->getSquaredDistance(curr_node, temp_y_it->second);
						if (curr_squared_distance <= min_squared_distance) {
							min_squared_distance = curr_squared_distance;
							nearest_node = temp_y_it;
						}
					}
					else {
						curr_squared_distance = this->eucl->getSquaredDistance(curr_node, temp_y_it->second);
						if (curr_squared_distance <= min_squared_distance) {
							min_squared_distance = curr_squared_distance;
							nearest_node = temp_y_it;
						}
					}
					temp_x_it--;
				}



				tour.push_back(curr_node);  // update tour
				xit->second.erase(yit);
				if (xit->second.size() == 0) {
					copyMap.erase(xit);
				}
				cost += sqrt(min_squared_distance); // add cost
				curr_node = nearest_node->second;  // move to new node

			}

		}
		// check if current tour is better than older one
		if (cost < this->cost) {
			this->cost = cost;
			this->tour.assign(tour.begin(), tour.end());
		}

		this->actualIteration++;  // increase solve count


	}



}


deque<Node> MapSearchGreedy::getStartIndexList() {
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