#ifndef TSP_BINARYGREEDY_H
#define TSP_BINARYGREEDY_H

#include <iostream>
#include <list>
#include <deque>
#include <random>
#include "AbstractSolver.h"
#include "Euclidean.h"

using namespace std;

class BinaryGreedy : public AbstractSolver {
protected:
	/**
	 * Tool for calculating euclidean distance
	 */
	Euclidean *eucl = new Euclidean();

protected:
	/**
	 * Solve TSP of current graph.
	 * Use basic greedy algorithm(nearest neighbor).
	 */
	void solve(int iteration, Timer &timer) override;

	/**
	 * Get randomly shuffled start node index list.
	 *
	 * @return
	 */
	deque<Node> getStartIndexList();
	list<list<Node>> makeNodeList();
};

#endif //TSP_BASICGREEDY_H
