#ifndef GRAPH_H
#define GRAPH_H
#include"Node.h"
#include<vector>
#include <queue>
#include <climits>
#include <fstream> 
#include <sstream> 
class Node;
class Graph {
	set<Node*> nodes;
public:
	Graph(const string& filename);
	~Graph();
	void addNode(Node* node);
	Node* addNode(const string& name);
	void removeNode(Node* node);
	void addEdge(Node* begin, Node* end, int weight);
	void addEdge(const std::string& name1, const std::string& name2, int weight);
	void removeEdge(Node* begin, Node* end);
	Node* findNode(const string& name);
	void showGraph();
	node_iterator begin() const { return nodes.begin(); }
	node_iterator end() const { return nodes.end(); }
	vector<string> dijkstraShortestPath(const string& startName, const string& endName);
	int dijkstraShortestDistance(const string& startName, const string& endName);
};

#endif 
