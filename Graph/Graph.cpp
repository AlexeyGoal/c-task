#include "Graph.h"


// Реализация методов Graph



Graph::Graph(const std::string& file_name) {
    std::ifstream file(file_name);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << file_name << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line); 

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string source, target;
        if (!(iss >> source >> target)) { break; }

        Node* srcNode = getOrCreateNode(source);
        Node* tgtNode = getOrCreateNode(target);

        addEdge(srcNode, tgtNode);
    }
}

Graph::~Graph() {
    for (auto& pair : nodeMap) {
        delete pair.second;
    }
}

void Graph::printNodes() {
    for (auto e : nodes) {
        std::cout << e->getName() << " ";
    }
}


Node* Graph::getOrCreateNode(const std::string& name) {
    if (nodeMap.find(name) == nodeMap.end()) {
        Node* newNode = new Node(name);
        nodeMap[name] = newNode;
        nodes.insert(newNode);
    }
    return nodeMap[name];
}


void Graph::addNode(Node* node) {
    nodes.insert(node);
    nodeMap[node->getName()] = node;
}

void Graph::removeNode(Node* node) {
    nodes.erase(node);
    nodeMap.erase(node->getName());
    for (node_iterator it = nodes.begin(); it != nodes.end(); it++) {
        (*it)->removeNeighbour(node);
    }
    delete node;
}

void Graph::addEdge(Node* begin, Node* end) {
    if (nodes.find(begin) == nodes.end() || nodes.find(end) == nodes.end()) {
        return;
    }
    begin->addNeighbour(end);
    end->addNeighbour(begin);
}

void Graph::removeEdge(Node* begin, Node* end) {
    if (nodes.find(begin) == nodes.end() || nodes.find(end) == nodes.end()) {
        return;
    }
    begin->removeNeighbour(end);
    end->removeNeighbour(begin);
}

node_iterator Graph::begin() const { return nodes.begin(); }
node_iterator Graph::end() const { return nodes.end(); }

Node* Graph::findNode(const std::string& name) const {
    auto it = nodeMap.find(name);
    return it != nodeMap.end() ? it->second : nullptr;
}



// реализация BFS
bool BFS::connected(Node* begin, Node* end) {
    std::queue<Node*> nodes; nodes.push(begin);
    std::set<Node*> visited;
    while (!nodes.empty()) {
        Node* next = nodes.front(); nodes.pop();
        if (end == next) return true;
        visited.insert(next);
        for (node_iterator it = next->nb_begin();it != next->nb_end(); it++)
            
            if (visited.find(*it) == visited.end())
                nodes.push(*it);
    }
    return false;
}
// реализация DFS 
bool DFS::connected(Node* begin, Node* end) {
    visited.clear(); return connected(begin, end, 0);
}
bool DFS::connected(Node* begin, Node* end, int depth) {
    if (begin == end) return true;
    visited.insert(begin);
    for (node_iterator it = begin->nb_begin();
        it != begin->nb_end(); it++) {
        if (visited.find(*it) == visited.end()) {
            if (connected(*it, end, depth + 1)) return true;
        }
    }
    return false;
}


