#include "Node.h"


Node::Node(const std::string& aname) : name(aname) {}

const std::string& Node::getName() const { return name; }

void Node::addNeighbour(Node* neighbour) {
    neighbours.insert(neighbour);
}

void Node::removeNeighbour(Node* neighbour) {
    neighbours.erase(neighbour);
}

Node::node_iterator Node::nb_begin() const { return neighbours.begin(); }
Node::node_iterator Node::nb_end() const { return neighbours.end(); }