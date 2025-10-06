#include "antAlgorithm.h"
#include <iostream>
#include <random>
#include <algorithm>
#include <limits>
#include <cmath>

using namespace std;


Ant::Ant(int numVertices) : pathLength(0.0) {
    visited.resize(numVertices, false);
}

void Ant::reset(int startVertex) {
    fill(visited.begin(), visited.end(), false);
    path.clear();
    pathLength = 0.0;
    visited[startVertex] = true;
    path.push_back(startVertex);
}


AntAlgorithm::AntAlgorithm(const Graph& g, int antCount, double alphaVal,
    double betaVal, double evaporationVal, double QVal, int maxIter)
    : graph(g), numAnts(antCount), alpha(alphaVal), beta(betaVal),
    evaporation(evaporationVal), Q(QVal), maxIterations(maxIter) {

    int n = graph.getNumVertices();
    pheromone.resize(n, vector<double>(n, 0.0));
    heuristic.resize(n, vector<double>(n, 0.0));
    ants.resize(numAnts, Ant(n));

    initializePheromones();
    initializeHeuristics();
}

void AntAlgorithm::initializePheromones() {
    int n = graph.getNumVertices();
    double initialPheromone = 1.0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (graph.hasEdge(i, j)) {
                pheromone[i][j] = initialPheromone;
            }
        }
    }
}

void AntAlgorithm::initializeHeuristics() {
    int n = graph.getNumVertices();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (graph.hasEdge(i, j) && graph.getWeight(i, j) > 0) {
                heuristic[i][j] = 1.0 / graph.getWeight(i, j);
            }
            else {
                heuristic[i][j] = 0.0;
            }
        }
    }
}

double AntAlgorithm::calculatePathLength(const vector<int>& path) const {
    double length = 0.0;
    int n = path.size();

    for (int i = 0; i < n - 1; i++) {
        length += graph.getWeight(path[i], path[i + 1]);
    }
    
    if (n > 1) {
        length += graph.getWeight(path[n - 1], path[0]);
    }

    return length;
}

int AntAlgorithm::selectNextVertex(const Ant& ant, int currentVertex) {
    vector<double> probabilities(graph.getNumVertices(), 0.0);
    double sum = 0.0;

    
    for (int i = 0; i < graph.getNumVertices(); i++) {
        if (!ant.visited[i] && graph.hasEdge(currentVertex, i)) {
            double pheromoneValue = pow(pheromone[currentVertex][i], alpha);
            double heuristicValue = pow(heuristic[currentVertex][i], beta);
            probabilities[i] = pheromoneValue * heuristicValue;
            sum += probabilities[i];
        }
    }

    if (sum == 0.0) {
        return -1; 
    }

    
    for (int i = 0; i < graph.getNumVertices(); i++) {
        probabilities[i] /= sum;
    }

    
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);
    double randomValue = dis(gen);
    double cumulative = 0.0;

    for (int i = 0; i < graph.getNumVertices(); i++) {
        cumulative += probabilities[i];
        if (randomValue <= cumulative) {
            return i;
        }
    }

    return -1;
}

double AntAlgorithm::getTransitionProbability(int from, int to, const Ant& ant) const {
    if (ant.visited[to] || !graph.hasEdge(from, to)) {
        return 0.0;
    }

    double numerator = pow(pheromone[from][to], alpha) * pow(heuristic[from][to], beta);
    double denominator = 0.0;

    for (int i = 0; i < graph.getNumVertices(); i++) {
        if (!ant.visited[i] && graph.hasEdge(from, i)) {
            denominator += pow(pheromone[from][i], alpha) * pow(heuristic[from][i], beta);
        }
    }

    return denominator > 0 ? numerator / denominator : 0.0;
}

void AntAlgorithm::updatePheromones() {
    int n = graph.getNumVertices();

    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            pheromone[i][j] *= (1.0 - evaporation);
        }
    }

    
    for (const Ant& ant : ants) {
        if (ant.path.size() == n) {
            double deltaPheromone = Q / ant.pathLength;

            
            for (int i = 0; i < n - 1; i++) {
                pheromone[ant.path[i]][ant.path[i + 1]] += deltaPheromone;
            }
            
            pheromone[ant.path[n - 1]][ant.path[0]] += deltaPheromone;
        }
    }
}

vector<int> AntAlgorithm::findShortestHamiltonianCycle() {
    int n = graph.getNumVertices();
    if (n == 0) return vector<int>();

    vector<int> bestCycle;
    double bestLength = numeric_limits<double>::max();

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> startDist(0, n - 1);

    for (int iteration = 0; iteration < maxIterations; iteration++) {
        
        for (int i = 0; i < numAnts; i++) {
            int startVertex = startDist(gen);
            ants[i].reset(startVertex);
        }

        
        for (Ant& ant : ants) {
            for (int step = 1; step < n; step++) {
                int currentVertex = ant.path.back();
                int nextVertex = selectNextVertex(ant, currentVertex);

                if (nextVertex == -1) {
                    
                    break;
                }

                ant.path.push_back(nextVertex);
                ant.visited[nextVertex] = true;
                ant.pathLength += graph.getWeight(currentVertex, nextVertex);
            }

            
            if (ant.path.size() == n) {
                ant.pathLength += graph.getWeight(ant.path.back(), ant.path[0]);

                
                if (ant.pathLength < bestLength) {
                    bestLength = ant.pathLength;
                    bestCycle = ant.path;
                }
            }
        }

        
        updatePheromones();

        
    }

    return bestCycle;
}

double AntAlgorithm::getCycleLength(const vector<int>& cycle) const {
    return calculatePathLength(cycle);
}