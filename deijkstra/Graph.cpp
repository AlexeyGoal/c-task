#include"Graph.h"


Graph::Graph(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Cannot open file: " + filename);
    }

    string line;
    bool firstLine = true; 

    while (getline(file, line)) {
        
        if (line.empty()) continue;

        
        if (firstLine) {
            firstLine = false;
            continue;
        }

        istringstream iss(line);
        string source, target, weightStr;

        
        if (getline(iss, source, '\t') &&
            getline(iss, target, '\t') &&
            getline(iss, weightStr)) {

            try {
                int weight = stoi(weightStr);

                
                Node* sourceNode = findNode(source);
                if (!sourceNode) {
                    sourceNode = addNode(source);
                }

                Node* targetNode = findNode(target);
                if (!targetNode) {
                    targetNode = addNode(target);
                }

                
                if (sourceNode && targetNode) {
                    addEdge(sourceNode, targetNode, weight);
                }

            }
            catch (const exception& e) {
                cerr << "Error parsing line: " << line << " - " << e.what() << endl;
                continue;
            }
        }
    }

    file.close();
}


Graph::~Graph() {
    
    for (Node* node : nodes) {
        delete node;
    }
    nodes.clear();
}

Node* Graph::findNode(const string& name) {
    for (Node* node : nodes) {
        if (node->getName() == name)
            return node;

    }
    return nullptr;
}

void Graph::addNode(Node* node) {
    if (findNode(node->getName()) != nullptr) {
        return; 
    }

    nodes.insert(node);
    
}

Node* Graph::addNode(const string& name) {
    if (findNode(name) != nullptr) {
        return nullptr; 
    }

    Node* newNode = new Node(name);
    nodes.insert(newNode);
    return newNode;
}

void Graph::removeNode(Node* node) {
    if (!node || nodes.find(node) == nodes.end()) {
        throw invalid_argument("There is no such vertex in the graph");
    }

    
    for (Node* other : nodes) {
        other->removeNeighbour(node);
    }

    
    nodes.erase(node);
    delete node;
    
}

void Graph::addEdge(Node* begin, Node* end, int weight) {
    if (!begin || !end || begin == end) {
        return;
    }

    if (nodes.find(begin) == nodes.end() || nodes.find(end) == nodes.end()) {
        return;
    }

    begin->addNeighbour(end, weight);
    end->addNeighbour(begin, weight);
}

void Graph::addEdge(const string& beginName, const string& endName, int weight) {
    Node* begin = findNode(beginName);
    Node* end = findNode(endName);

    if (begin && end) {
        addEdge(begin, end, weight);
    }
}


void Graph::removeEdge(Node* begin, Node* end) {
    if (!begin || !end) {
        return;
    }

    begin->removeNeighbour(end);
    end->removeNeighbour(begin);
}

void Graph::showGraph() {
    cout << "All vertexes:" << endl;
    for (Node* node : nodes)
        cout << node->getName() << endl;

    for (Node* node : nodes) {
        int cntN = node->neighbours.size();
        cout << node->getName() + " has " << cntN << " neighbours:" << endl;

        for (Node* neigh : node->neighbours) {
            int weight = node->getWeight(neigh);
            cout << "  " << neigh->getName() << " (weight: " << weight << ")" << endl;
        }
    }
}

vector<string> Graph::dijkstraShortestPath(const string& startName, const string& endName) {
    Node* start = findNode(startName);
    Node* end = findNode(endName);

    if (!start || !end) {
        throw invalid_argument("Start or end node not found");
    }

    if (start == end) {
        return { startName };
    }

    
    map<Node*, int> distances;
    
    map<Node*, Node*> previous;
    
    priority_queue<pair<int, Node*>,
        vector<std::pair<int, Node*>>,
        greater<std::pair<int, Node*>>> pq;

    
    for (Node* node : nodes) {
        if (node == start) {
            distances[node] = 0;
        }
        else {
            distances[node] = INT_MAX;
        }
        previous[node] = nullptr;
    }

    pq.push({ 0, start });

    while (!pq.empty()) {
        Node* current = pq.top().second;
        int currentDistance = pq.top().first;
        pq.pop();

        
        if (current == end) {
            break;
        }

        
        if (currentDistance > distances[current]) {
            continue;
        }

        
        for (Node* neighbor : current->neighbours) {
            int weight = current->getWeight(neighbor);
            int newDistance = distances[current] + weight;

            if (newDistance < distances[neighbor]) {
                distances[neighbor] = newDistance;
                previous[neighbor] = current;
                pq.push({ newDistance, neighbor });
            }
        }
    }

    
    vector<string> path;
    Node* current = end;

    
    if (previous[current] == nullptr && current != start) {
        return {}; 
    }

    while (current != nullptr) {
        path.push_back(current->getName());
        current = previous[current];
    }

    reverse(path.begin(), path.end());
    return path;
}


int Graph::dijkstraShortestDistance(const string& startName, const string& endName) {
    Node* start = findNode(startName);
    Node* end = findNode(endName);

    if (!start || !end) {
        throw std::invalid_argument("Start or end node not found");
    }

    if (start == end) {
        return 0;
    }

    map<Node*, int> distances;
    priority_queue<pair<int, Node*>,
        vector<pair<int, Node*>>,
        greater<pair<int, Node*>>> pq;

    for (Node* node : nodes) {
        if (node == start) {
            distances[node] = 0;
        }
        else {
            distances[node] = INT_MAX;
        }
    }

    pq.push({ 0, start });

    while (!pq.empty()) {
        Node* current = pq.top().second;
        int currentDistance = pq.top().first;
        pq.pop();

        if (current == end) {
            return distances[end];
        }

        if (currentDistance > distances[current]) {
            continue;
        }

        for (Node* neighbor : current->neighbours) {
            int weight = current->getWeight(neighbor);
            int newDistance = distances[current] + weight;

            if (newDistance < distances[neighbor]) {
                distances[neighbor] = newDistance;
                pq.push({ newDistance, neighbor });
            }
        }
    }

    return -1; 
}