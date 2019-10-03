#ifndef TSP_TIMER_H
#define TSP_TIMER_H

#include <chrono>

using namespace std;

class Timer {
 private:
  chrono::system_clock::time_point startTime;

  double timeLimit = 0.;

 public:
  Timer(double limit_seconds);

  void start();

  double getElapsedTime();

  bool isOver();
};

#endif //TSP_TIMER_H
