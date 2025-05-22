#ifndef GRAPH_H
#define GRAPH_H

#include "Node.h"
#include <queue>
#include <algorithm>
#include <unordered_set>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>


class Graph {
    std::set<Node*> nodes;
    std::map<std::string, Node*> nodeMap;
    Node* getOrCreateNode(const std::string& name);
public:

    Graph(const std::string& file_name);
    ~Graph();

    void addNode(Node* node);
    void printNodes();
    void removeNode(Node* node);
    void addEdge(Node* begin, Node* end);
    void removeEdge(Node* begin, Node* end);
    node_iterator begin() const;
    node_iterator end() const;
    Node* findNode(const std::string& name) const;
};

class BFS {
    const Graph& graph;
public:
    BFS(const Graph& agraph) : graph(agraph) {}
    bool connected(Node* begin, Node* end);
};

class DFS {
    const Graph& graph;
    std::set<Node*> visited;
    bool connected(Node* begin, Node* end, int depth);
public:
    DFS(const Graph& agraph) : graph(agraph) {}
    bool connected(Node* begin, Node* end);
};

#endif
