#ifndef TSP_MAPSEARCHGREEDY_H
#define TSP_MAPSEARCHGREEDY_H

#include <iostream>
#include <list>
#include <deque>
#include <random>
#include <map>
#include <algorithm>

#include "AbstractSolver.h"
#include "./tool/Euclidean.h"
using namespace std;

class MapSearchGreedy : public AbstractSolver {
protected:
	/**
	 * Tool for calculating euclidean distance
	 */
	Euclidean* eucl = new Euclidean();

protected:
	/**
	 * Solve TSP of current graph.
	 * Use basic greedy algorithm(nearest neighbor).
	 */
	void solve(Timer &timer, long long iteration) override;

	/**
	 * Get randomly shuffled start node index list.
	 *
	 * @return
	 */
	deque<Node> getStartIndexList();
};

#endif //TSP_MAPSEARCHGREEDY_H
