#ifndef NODE_H
#define NODE_H

#include <set>
#include <string>



class Node;

typedef std::set<Node*>::const_iterator node_iterator;

class Node {
    std::string name;
    std::set<Node*> neighbours;

    void addNeighbour(Node* neighbour);
    void removeNeighbour(Node* neighbour);

public:
    Node(const std::string& aname);
    const std::string& getName() const;

    typedef std::set<Node*>::const_iterator node_iterator;
    node_iterator nb_begin() const;
    node_iterator nb_end() const;

    friend class Graph;
};




#endif 
