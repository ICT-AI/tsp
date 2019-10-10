#include "MSTGreedy.h"
#include <iostream>
void MSTGreedy::solve(Timer &timer, long long iteration) {
  primMST();
  findOddIndices();
  perfectMatching();
  makeEulerian();
  makeHamiltonian();

  this->cost = 0.;
  for (auto iter = this->tour.begin(); iter != this->tour.end() - 1; iter++) {
    this->cost += this->eucl->getDistance(*iter, *(iter + 1));
  }

  this->actualIteration++;
}

void MSTGreedy::primMST() {
  vector<Node> nodes(this->graph->getNodes());
  vector<long long> distances(nodes.size(), LL_MAX);
  vector<int> from(nodes.size());
  from[0] = -1;

  long long temp_dist;
  int curr_index = 0, min_index;
  long long min_dist;
  for (int i = 0; i < nodes.size() - 1; i++) {
    distances[curr_index] = 0;

    min_index = -1;
    min_dist = LL_MAX;
    for (int j = 0; j < nodes.size(); j++) {
      if (distances[j] == 0) {
        continue;
      }

      temp_dist = this->eucl->getSquaredDistance(nodes[curr_index], nodes[j]);
      if (temp_dist < distances[j]) {
        distances[j] = temp_dist;
        from[j] = curr_index;
      }

      if (distances[j] < min_dist) {
        min_dist = distances[j];
        min_index = j;
      }
    }

    curr_index = min_index;
  }

  // create minimum spanning tree
  this->mst.assign(from.size(), deque<int>());
  int n1, n2;
  for (int i = 1; i < from.size(); i++) {
    n1 = i;
    n2 = from[i];

    mst[n1].push_back(n2);
    mst[n2].push_back(n1);
  }
}

void MSTGreedy::findOddIndices() {
  for (int i = 0; i < this->mst.size(); i++) {
    if ((this->mst[i].size() % 2) == 1) {
      this->oddIndices.push_back(i);
    }
  }
}

void MSTGreedy::perfectMatching() {
  vector<Node> nodes(this->graph->getNodes());
  vector<int>::iterator curr, next, nearest;
  long long min, temp_dist;

  while (!this->oddIndices.empty()) {
    curr = this->oddIndices.begin();
    min = LL_MAX;
    for (next = curr + 1; next != this->oddIndices.end(); next++) {
      temp_dist = this->eucl->getSquaredDistance(nodes[*curr], nodes[*next]);

      if (temp_dist < min) {
        min = temp_dist;
        nearest = next;
      }
    }

    this->mst[*curr].push_back(*nearest);
    this->mst[*nearest].push_back(*curr);

    this->oddIndices.erase(nearest);
    this->oddIndices.erase(curr);
  }
}

void MSTGreedy::makeEulerian() {
  vector<deque<int>> temp_mst(this->mst);
  stack<int> stack;

  int curr = 0, neighbor;
  while (!temp_mst[curr].empty() || !stack.empty()) {
    if (temp_mst[curr].empty()) { // if current vertex has no neighbors
      this->eulerian.push_back(curr);
      curr = stack.top();
      stack.pop();
    } else {  // otherwise (in case it has neighbors)
      stack.push(curr);
      neighbor = temp_mst[curr].front();
      temp_mst[curr].pop_front();

      for (auto iter = temp_mst[neighbor].begin(); iter != temp_mst[neighbor].end(); iter++) {
        if (*iter == curr) {
          temp_mst[neighbor].erase(iter);
          break;
        }
      }

      curr = neighbor;
    }
  }

  this->eulerian.push_back(curr);
}

void MSTGreedy::makeHamiltonian() {
  vector<Node> nodes(this->graph->getNodes());
  vector<bool> visited(nodes.size(), false);

  for (auto iter = this->eulerian.rbegin(); iter != this->eulerian.rend(); iter++) {
    if (!visited[*iter]) {
      this->tour.push_back(nodes[*iter]);
      visited[*iter] = true;
    }
  }
}
