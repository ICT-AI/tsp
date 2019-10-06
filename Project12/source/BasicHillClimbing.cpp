#include "../header/BasicHillClimbing.h"

void BasicHillClimbing::solve(int iteration, Timer &timer) {
	// initialize random tour
	this->tour.assign(this->graph->getNodes().begin(), this->graph->getNodes().end());
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	shuffle(this->tour.begin(), this->tour.end(), default_random_engine(seed));

	// solve once
	this->actualIteration = 1;

	Node broken1_from, broken1_to, broken2_from, broken2_to;
	float broken1_distance, broken2_distance, new1_distance, new2_distance;
	while (iteration) {
		for (int i = 0; i < this->tour.size() - 1; i++) {
			if (timer.isOver()) {
				return;
			}

			broken1_from = this->tour[i];
			broken1_to = this->tour[i + 1];
			for (int j = 0; j < this->tour.size() - 1; j++) {
				broken2_from = this->tour[j];
				broken2_to = this->tour[j + 1];

				if (i == j) {}
				else if (i - j == 1) {}
				else if (j - i == 1) {}
				else {
					broken1_distance = this->eucl->getDistance(broken1_from, broken1_to);
					broken2_distance = this->eucl->getDistance(broken2_from, broken2_to);
					new1_distance = this->eucl->getDistance(broken1_from, broken2_from);
					new2_distance = this->eucl->getDistance(broken1_to, broken2_to);

					if (new1_distance + new2_distance < broken1_distance + broken2_distance) {
						// swap
						this->tour[i + 1].index = broken2_from.index;
						this->tour[i + 1].x = broken2_from.x;
						this->tour[i + 1].y = broken2_from.y;

						this->tour[j].index = broken1_to.index;
						this->tour[j].x = broken1_to.x;
						this->tour[j].y = broken1_to.y;

						break;
					}
				}
			}
		}

		iteration--;
	}

	this->cost = 0;
	for (auto iter = this->tour.begin(); iter != this->tour.end() - 1; iter++) {
		cost += this->eucl->getDistance(*iter, *(iter + 1));
	}
}
