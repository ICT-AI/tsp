#include "Hillclimbing.h"

Hillclimbing::Hillclimbing(Graph *g) {
    this->graph = g;
}

void Hillclimbing::solve() {
    //run random function given data's times for pick random road.
    //Start at the first point, pick first 4 points.
    //Choose a middle point of 2, 3.
    //Exchange each other, and compare costs before and after.
    //If it gets better in after, change two points.
    //If not, 
    int diff;
    int curr_distance = 0;
    int new_distance = 0;

    // Randomize the tour.
    for (int i=0; i<size; i++) {
        tour[i] = rand()%size
    }

    list<Node> unvisited_nodes(this->graph->getNodes().begin(), this->graph->getNodes().end());
    unvisited_nodes.sort();

    list<Node>::iterator iter, nn;
    float total_cost = 0.0;
    this->tour.reserve(this->graph->getNodes().size());

    // start the node which is nearest from origin.
    //Node curr_node = unvisited_nodes.front();
    //unvisited_nodes.erase(unvisited_nodes.begin());
    //this->tour.push_back(curr_node.index);

    //running the algorithm by given times.
    for (int j=0; j<10; j++) {
        for () {
        move(startPoint);
        }
    }
    
}

void Hillclimbing::move(int startPoint) {
    
} 