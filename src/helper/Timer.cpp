#include "Timer.h"

Timer::Timer(double limit_seconds) {
  this->timeLimit = limit_seconds;
}

void Timer::start() {
  this->startTime = chrono::system_clock::now();
}

double Timer::getElapsedTime() {
  chrono::duration<double> elapsed = chrono::system_clock::now() - this->startTime; // measure elapsed time

  return elapsed.count();
}

double Timer::getRemainingTime() {
  return this->timeLimit - this->getElapsedTime();
}

bool Timer::isOver() {
  return (this->getElapsedTime() >= this->timeLimit);
}
