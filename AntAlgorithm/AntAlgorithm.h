#ifndef ANTALGORITHM_H
#define ANTALGORITHM_H

#include "DirectedGraph.h"
#include <vector>



struct Ant {
    vector<int> path;
    vector<bool> visited;
    double pathLength;

    Ant(int numVertices);
    void reset(int startVertex);
};

class AntAlgorithm {
private:
    const Graph& graph;
    vector<vector<double>> pheromone;
    vector<vector<double>> heuristic;
    vector<Ant> ants;

    
    int numAnts;
    double alpha;        
    double beta;         
    double evaporation;  
    double Q;            
    int maxIterations;

    void initializePheromones();
    void initializeHeuristics();
    double calculatePathLength(const vector<int>& path) const;
    int selectNextVertex(const Ant& ant, int currentVertex);
    void updatePheromones();
    double getTransitionProbability(int from, int to, const Ant& ant) const;

public:
    AntAlgorithm(const Graph& g, int antCount = 10, double alpha = 1.0,
        double beta = 2.0, double evaporation = 0.5,
        double Q = 100.0, int maxIter = 100);

    vector<int> findShortestHamiltonianCycle();
    double getCycleLength(const vector<int>& cycle) const;
};

 

#endif