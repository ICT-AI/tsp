#include "SequentialGreedy.h"

void SequentialGreedy::solve(Timer &timer, long long iteration) {
  sort(this->graph->getNodes().begin(), this->graph->getNodes().end()); // sort graph node list
  deque<int> start_index_list = this->getStartIndexList();  // start node index list for iterative solving

  // until specified iteration or entire node size
  for (int i = 0; i < min(iteration, (long long)this->graph->getNodes().size()); i++) {
    // check if time is over
    if (timer.isOver()) {
      return;
    }

    // initialize unvisited nodes, cost, tour
    list<Node> unvisited_nodes(this->graph->getNodes().begin(), this->graph->getNodes().end());
    float cost = 0.0;
    vector<Node> tour;
    tour.reserve(this->graph->getNodes().size());

    // set the starting node
    int start_index = start_index_list.front();
    start_index_list.pop_front();
    Node curr_node;
    for (auto iter = unvisited_nodes.begin(); iter != unvisited_nodes.end(); iter++) {
      if (iter->index == start_index) {
        curr_node = *iter;
        unvisited_nodes.erase(iter);
        tour.push_back(curr_node);
      }
    }

    list<Node>::iterator nearest_node;
    long long min_squared_distance, x_squared_distance, curr_squared_distance;
    // until visit all nodes
    while (!unvisited_nodes.empty()) {
      min_squared_distance = LL_MAX;
      for (auto iter = unvisited_nodes.begin(); iter != unvisited_nodes.end(); iter++) {
        // for early stop
        // check if x distance is greater than minimum distance
        x_squared_distance = this->eucl->getSquaredDistance(curr_node.x, 0, (*iter).x, 0);
        if (x_squared_distance > min_squared_distance) {
          break;
        }

        // check if found closer node
        // and update nearest node
        curr_squared_distance = this->eucl->getSquaredDistance(curr_node, *iter);
        if (curr_squared_distance < min_squared_distance) {
          min_squared_distance = curr_squared_distance;
          nearest_node = iter;
        }
      }

      curr_node = *nearest_node;  // move to new node
      unvisited_nodes.erase(nearest_node);  // delete new node from unvisited node list
      cost += sqrt(min_squared_distance); // add cost
      tour.push_back(curr_node);  // update tour
    }

    // check if current tour is better than older one
    if (cost < this->cost) {
      this->cost = cost;
      this->tour.assign(tour.begin(), tour.end());
    }

    this->actualIteration++;  // increase solve count
  }
}

deque<int> SequentialGreedy::getStartIndexList() {
  deque<int> start_index_list;
  // copy from original node list
  for (auto node : this->graph->getNodes()) {
    start_index_list.push_back(node.index);
  }

  // pop first and last index which are should be run
  int front = start_index_list.front();
  int back = start_index_list.back();
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