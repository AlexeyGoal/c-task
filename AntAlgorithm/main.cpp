#include <iostream>
#include <iomanip>
#include "DirectedGraph.h"
#include "antAlgorithm.h"

using namespace std;

void printCycle(const vector<int>& cycle, double length) {
    cout << "Hamiltonian cycle: ";
    for (size_t i = 0; i < cycle.size(); i++) {
        cout << cycle[i]+1;
        if (i < cycle.size() - 1) {
            cout << " -> ";
        }
    }
    cout << " -> " << cycle[0] +1<< endl;
    cout << "length of the cycle: " << length << endl;
}

int main() {
    
    Graph graph(6, true); 

    
    graph.addEdge(0, 1, 3.0);
    graph.addEdge(0, 4, 1.0);
    

    graph.addEdge(1, 0, 3.0);
    graph.addEdge(1, 2, 8.0);
    graph.addEdge(1, 5, 3.0);
    

    graph.addEdge(2, 1, 3.0);
    graph.addEdge(2, 3, 1.0);
    graph.addEdge(2, 5, 1.0);
    

    graph.addEdge(3, 2, 8.0);
    graph.addEdge(3, 4, 1.0);
    

    graph.addEdge(4, 0, 3.0);
    graph.addEdge(4, 3, 3.0);


    graph.addEdge(5, 0, 3.0);
    graph.addEdge(5, 1, 3.0);
    graph.addEdge(5, 2, 3.0);
    graph.addEdge(5, 3, 5.0);
    graph.addEdge(5, 4, 4.0);
   
   
    AntAlgorithm antAlgo(graph, 15, 1.0, 3.0, 0.3, 100.0, 200);

    
    
    vector<int> bestCycle = antAlgo.findShortestHamiltonianCycle();
    double bestLength = antAlgo.getCycleLength(bestCycle);

    cout << "Result:" << endl;
    printCycle(bestCycle, bestLength);

    return 0;
}
