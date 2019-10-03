#include "Euclidean.h"

float Euclidean::getDistance(int x1, int y1, int x2, int y2) {
  float dx = x1 - x2;
  float dy = y1 - y2;

  return sqrt(dx * dx + dy * dy);
}

float Euclidean::getDistance(Node &n1, Node &n2) {
  return this->getDistance(n1.x, n1.y, n2.x, n2.y);
}

long long Euclidean::getSquaredDistance(int x1, int y1, int x2, int y2) {
  long long dx = x1 - x2;
  long long dy = y1 - y2;

  return dx * dx + dy * dy;
}

long long Euclidean::getSquaredDistance(Node &n1, Node &n2) {
  return this->getSquaredDistance(n1.x, n1.y, n2.x, n2.y);
}