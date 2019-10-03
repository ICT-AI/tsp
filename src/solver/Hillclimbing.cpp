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
}