#ifndef TSP_NODE_H
#define TSP_NODE_H

class Node {
 public:
  /**
   * Node index
   */
  int index;

  /**
   * x coordinate
   */
  int x;

  /**
   * y coordinate
   */
  int y;

 public:
  Node();

  Node(int index, int x, int y);

  /**
   * Operator `<` for Node object.
   * For node sorting.
   *
   * @param node
   * @return
   */
  bool operator <(const Node &node) const;
};

#endif //TSP_NODE_H
