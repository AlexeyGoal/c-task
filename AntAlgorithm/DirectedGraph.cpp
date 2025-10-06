#include "DirectedGraph.h"
#include <iostream>
#include <iomanip>

using namespace std;

Graph::Graph(int vertices, bool directed)
    : numVertices(vertices), isDirected(directed) {
    adjacencyMatrix.resize(numVertices, vector<double>(numVertices, 0.0));
}

Graph::~Graph() {}

void Graph::addEdge(int from, int to, double weight) {
    if (from >= 0 && from < numVertices && to >= 0 && to < numVertices) {
        adjacencyMatrix[from][to] = weight;
        if (!isDirected) {
            adjacencyMatrix[to][from] = weight;
        }
    }
}

double Graph::getWeight(int from, int to) const {
    if (from >= 0 && from < numVertices && to >= 0 && to < numVertices) {
        return adjacencyMatrix[from][to];
    }
    return 0.0;
}

bool Graph::hasEdge(int from, int to) const {
    if (from >= 0 && from < numVertices && to >= 0 && to < numVertices) {
        return adjacencyMatrix[from][to] > 0.0;
    }
    return false;
}

int Graph::getNumVertices() const {
    return numVertices;
}

bool Graph::isComplete() const {
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            if (i != j && adjacencyMatrix[i][j] == 0.0) {
                return false;
            }
        }
    }
    return true;
}

void Graph::printGraph() const {
    cout << "Матрица смежности графа (" << numVertices << " вершин):" << endl;
    cout << "   ";
    for (int i = 0; i < numVertices; i++) {
        cout << setw(4) << i;
    }
    cout << endl;

    for (int i = 0; i < numVertices; i++) {
        cout << setw(2) << i << " ";
        for (int j = 0; j < numVertices; j++) {
            cout << setw(4) << adjacencyMatrix[i][j];
        }
        cout << endl;
    }
}

vector<int> Graph::getNeighbors(int vertex) const {
    vector<int> neighbors;
    if (vertex >= 0 && vertex < numVertices) {
        for (int i = 0; i < numVertices; i++) {
            if (adjacencyMatrix[vertex][i] > 0.0) {
                neighbors.push_back(i);
            }
        }
    }
    return neighbors;
}