#include"Node.h"

Node::~Node() {
    neighbours.clear();
    weights.clear();
}

void Node::addNeighbour(Node* neighbour, int weight) {
    if (neighbour && neighbour != this) {
        neighbours.insert(neighbour);
        weights[neighbour] = weight;
    }
}

void Node::removeNeighbour(Node* neighbour) {
    if (neighbour) {
        neighbours.erase(neighbour);
        weights.erase(neighbour);
    }
}

int Node::getWeight(Node* neighbour) const {
    auto it = weights.find(neighbour);
    if (it != weights.end()) {
        return it->second;
    }
    return 0; 
}