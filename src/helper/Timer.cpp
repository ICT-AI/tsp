#include "Timer.h"

Timer::Timer(double limit_seconds) {
  this->timeLimit = limit_seconds;
}

void Timer::start() {
  this->startTime = chrono::system_clock::now();
}

double Timer::getElapsedTime() {
  chrono::duration<double> elapsed = chrono::system_clock::now() - this->startTime;

  return elapsed.count();
}

bool Timer::isOver() {
  return (this->getElapsedTime() >= this->timeLimit);
}
