#include "../header/Node.h"

Node::Node() {
	this->index = 0;
	this->x = 0;
	this->y = 0;
}

Node::Node(int index, int x, int y) {
	this->index = index;
	this->x = x;
	this->y = y;
}

bool Node::operator <(const Node &node) const {
	// first, compare x
	// and then compare y
	if (this->x == node.x) {
		return this->y < node.y;
	}
	else {
		return this->x < node.x;
	}
}