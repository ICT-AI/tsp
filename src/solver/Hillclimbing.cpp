#include "Hillclimbing.h"

pair<int, int> make_sorted_pair(int x, int y) {
  if (x < y) {
    return make_pair(x, y);
  } else {
    return make_pair(y, x);
  }
}

LKMatrix::LKMatrix(Graph *g) {
    this->graph = g;
}

LKMatrix::LKMatrix(vector<pair<double, double> > &coords, vector<int> &ids) {
  this->coords = coords;
  this->ids = ids;
  size = ids.size();

  // initialize tour
  tour = vector<int>(size, 0);

  // initial 'random' tour
  for (int i = 0; i < size; i++) {
    tour[i] = (i + 1) % size;
  }

  // sets the distanceVector
  edgeDistances = vector<vector<double> > (size, vector<double> (size, 0));

  double edgeDistance;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {

      // Compute the edge distance
      edgeDistance = sqrt(pow((coords[i].first - coords[j].first), 2) +
          pow((coords[i].second - coords[j].second), 2));
      edgeDistances[i][j] = edgeDistance;
      edgeDistances[j][i] = edgeDistance;
    }
  }
}

double LKMatrix::getCurrentTourDistance() {
  double distance = 0;
  for (int i = 0; i < size; i++) {
    distance += edgeDistances[i][tour[i]];
  }
  return distance;
}

void LKMatrix::LKMove(int tourStart) {
  set<pair<int,int> > broken_set, joined_set;
  vector<int> tour_opt = tour;
  double g_opt = 0;
  double g = 0; // := G_i
  double g_local; // := g_i
  int lastNextV = tourStart;
  int fromV;
  int nextV;
  int nextFromV;
  int lastPossibleNextV;
  pair<int, int> broken_edge;
  double y_opt_length;
  double broken_edge_length;
  double g_opt_local;

  fromV = tour[lastNextV];
  
    do {
        srand((unsigned int)time(NULL));
        int proba=(int)(rand()%100);
      
    // default, no nextV is found
    nextV = -1;

    broken_edge = make_sorted_pair(lastNextV, fromV); // := x_i
    broken_edge_length = edgeDistances[broken_edge.first][broken_edge.second];

    if (joined_set.count(broken_edge) > 0) break;

    for (int possibleNextV = tour[fromV]; nextV == -1 && possibleNextV != tourStart; possibleNextV = tour[possibleNextV]) {

      // calculate local gain
      g_local = broken_edge_length - edgeDistances[fromV][possibleNextV];

      // conditions that make this edge not a valid y_i
      if (!(broken_set.count(make_sorted_pair(fromV, possibleNextV)) == 0 &&g + g_local > 0 && joined_set.count(make_sorted_pair(lastPossibleNextV, possibleNextV)) == 0 &&tour[possibleNextV] != 0 && possibleNextV != tour[fromV]
      )) {
        lastPossibleNextV = possibleNextV;
        continue;
      }

      nextV = possibleNextV;
    }

    // a next y_i exists
    if (nextV != -1) {

      // add to our broken_set and joined_set
      broken_set.insert(broken_edge);
      joined_set.insert(make_sorted_pair(fromV, nextV));

      // condition 4(f)
      y_opt_length = edgeDistances[fromV][tourStart]; // y_i_opt
      
      // The tour length if we exchanged the broken edge (x_i)
      // with y_opt, (t_{2i}, t_0)
      g_opt_local = g + (broken_edge_length - y_opt_length);
        
      if (g_opt_local > g_opt) {
        g_opt = g_opt_local;
        tour_opt = tour;
        // join the optimal tour
        tour_opt[tourStart] = fromV;
      } else if(proba<=60){
          g_opt = g_opt_local;
          tour_opt = tour;
          // join the optimal tour
          tour_opt[tourStart] = fromV;
      }

      // recalculate g
      g += broken_edge_length - edgeDistances[fromV][nextV];

      // reverse tour direction between newNextV and fromV
      // implicitly breaks x_i
      reverse(fromV, lastPossibleNextV);

      // remember our new t_{2i+1}
      nextFromV = lastPossibleNextV;
      //cout << "Joined to " << nextFromV << endl;

      // build y_i
      tour[fromV] = nextV;
      
      // set new fromV to t_{2i+1}
      // and out lastNextV to t_{2i}
      lastNextV = nextV;
      fromV = nextFromV;

    }

  } while (nextV != -1);

  tour = tour_opt;

  printTour();
}

void LKMatrix::solve() {
    /***run random function given data's times for pick random road.
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
    ***/

  int diff;
  int old_distance = 0;
  int new_distance = 0;
    
  for (long j = 0; j < 100; j++) {
    for (int i = 0; i < size; i++) {
      LKMove(i);
    }
    new_distance = getCurrentTourDistance();
    diff = old_distance - new_distance;
    if (j != 0) {
     // assert(diff >= 0);
      if (diff == 0) {
        //break;
      }
    }
    old_distance = new_distance;
  }
}

//Reverse the tour between indices start and end
void LKMatrix::reverse(int start, int end) {
  int current = start;
  int next = tour[start];
  int nextNext;
  do {
    nextNext = tour[next];

    tour[next] = current;

    // move to the next pointer
    current = next;
    next = nextNext;
  } while (current != end); // terminate once we've reversed up to end
}

// Sanity check function
bool LKMatrix::isTour() {
  int count = 1;
  int start = tour[0];
  while (start != 0) {
    start = tour[start];
    count++;
  }
  return (count == size);
}

void LKMatrix::printTour() {
  int current = 0;
  do {
    current = tour[current];
  } while (current != 0);
  cout<<this->getCurrentTourDistance()<<endl;
}

void LKMatrix::printTourIds() {
  int current = 0;
  do {
    cout << ids[current] << endl;
    current = tour[current];
  } while (current != 0);
  cout<<this->getCurrentTourDistance()<<"hi"<<endl;
}

void init(const char* file_name){
    int pointCnt = 0;
    FILE* fp = fopen(file_name, "r");
    fscanf(fp, "%d", &pointCnt);
    for (int i = 0; i < pointCnt; i++) {
        int num, x, y;
        fscanf(fp, "%d %d %d", &num, &x, &y);
        id.push_back(num);
        coord.push_back(make_pair(x, y));
        nodes.push_back(make_pair(x,y));
    }
    fclose(fp);
    return;
}

void LKMatrix::indexForDraw(){//tour에서의 방문순서에 따라 배열을 생성
    int i=0;
    int current=0;
    
    while(1){
        nodes[i].first=(coord[tour[current]]).first;
        nodes[i].second=(coord[tour[current]]).second;
        if(i>=size){
            break;}
        i++;
        current=tour[current];
    }
    return;
}