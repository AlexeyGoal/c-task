
#include"Graph.h"

// функция для сохранения компоненты в файл
void saveComponent(const std::set<Node*>& component, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    outFile << "Source\tTarget\n";
    std::set<std::pair<std::string, std::string>> edges;

    for (Node* node : component) {
        for (auto it = node->nb_begin(); it != node->nb_end(); ++it) {
            Node* neighbor = *it;
            // Проверяем, что сосед тоже в компоненте
            if (component.find(neighbor) != component.end()) {
                std::string source = node->getName();
                std::string target = neighbor->getName();
                if (source > target) std::swap(source, target);
                edges.insert({ source, target });
            }
        }
    }

    for (const auto& edge : edges) {
        outFile << edge.first << "\t" << edge.second << "\n";
    }
}

// функция для решение задачи
void findAndSaveGraph(Graph& graph) {
    std::set<Node*> visited;
    int componentCount = 0;
    BFS bfs(graph);

    for (auto it = graph.begin(); it != graph.end(); ++it) {
        Node* currentNode = *it;

        // Пропускаем уже посещённые узлы
        if (visited.find(currentNode) != visited.end()) {
            continue;
        }

        // Новая компонента связности
        componentCount++;
        std::set<Node*> currentComponent;
        std::queue<Node*> toProcess;
        toProcess.push(currentNode);
        visited.insert(currentNode);
        currentComponent.insert(currentNode);

        // Обход BFS
        while (!toProcess.empty()) {
            Node* node = toProcess.front();
            toProcess.pop();

            // Добавляем всех соседей
            for (auto neighbourIt = node->nb_begin(); neighbourIt != node->nb_end(); ++neighbourIt) {
                Node* neighbour = *neighbourIt;
                if (visited.find(neighbour) == visited.end()) {
                    visited.insert(neighbour);
                    currentComponent.insert(neighbour);
                    toProcess.push(neighbour);
                }
            }
        }

        // Сохраняем компоненту в файл
        saveComponent(currentComponent, "component_" + std::to_string(componentCount) + ".txt");
    }
}


int main()
{
    Graph graph("testgraph.txt");
    findAndSaveGraph(graph);

    Graph graph2("1000.csv");
    findAndSaveGraph(graph2);
        
    return 0;
}


