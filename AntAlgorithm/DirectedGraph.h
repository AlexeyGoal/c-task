#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>

using namespace std;

class Graph {
    private:
    vector<vector<double>> adjacencyMatrix;
    int numVertices;
    bool isDirected;

public:
    Graph(int vertices, bool directed = true);
    ~Graph();

    void addEdge(int from, int to, double weight);
    double getWeight(int from, int to) const;
    bool hasEdge(int from, int to) const;
    int getNumVertices() const;
    bool isComplete() const;
    void printGraph() const;
    vector<int> getNeighbors(int vertex) const;
};



#endif