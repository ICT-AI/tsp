#ifndef TSP_TIMER_H
#define TSP_TIMER_H

#include <chrono>

using namespace std;

class Timer {
 private:
  chrono::system_clock::time_point startTime;

  double timeLimit = 0.;

 public:
  /**
   * Create Timer object and set time limit.
   *
   * @param limit_seconds
   */
  Timer(double limit_seconds);

  /**
   * Start timer.
   */
  void start();

  /**
   * Get current elapsed time.
   *
   * @return
   */
  double getElapsedTime();

  /**
   * Check if time is over.
   *
   * @return
   */
  bool isOver();
};

#endif //TSP_TIMER_H
