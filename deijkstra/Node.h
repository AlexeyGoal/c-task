#ifndef NODE_H
#define NODE_H 
using namespace std;
#include<set>
#include<string>
#include <iostream>
#include<map>

class Node;

typedef std::set<Node*>::const_iterator node_iterator;
class Node {
	string name;
	set<Node*> neighbours;
	map<Node*, int> weights;
	void addNeighbour(Node* neighbour,int weight);
	void removeNeighbour(Node* neighbour);
public:
	Node(const string& aname) : name(aname){}
	~Node();
	const string& getName() const { return name; }
	node_iterator nb_begin() const { return neighbours.begin(); }
	node_iterator nb_end() const { return neighbours.end(); }
	int getWeight(Node* neighbour) const;
	friend class Graph;
};

#endif
