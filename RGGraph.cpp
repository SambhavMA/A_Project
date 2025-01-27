
#include "RGGraph.h"

// Calcula la distancia euclidiana entre dos nodos
double distance(const Node& a, const Node& b) {
    double dist = 0.0;
    for (size_t i = 0; i < a.coords.size(); ++i) {
        dist += (a.coords[i] - b.coords[i]) * (a.coords[i] - b.coords[i]);
    }
    return std::sqrt(dist);
}

RandomGeometricGraph::RandomGeometricGraph(int numNodes, double initialRadius, int dimensions)
    : numNodes(numNodes), radius(initialRadius), dimensions(dimensions) {
    generateNodes();  // Genera los nodos únicos
    createEdges();    // Crea las aristas
}

// Imprime los nodos y sus conexiones
void RandomGeometricGraph::printGraph() const {
    for (size_t i = 0; i < edges.size(); ++i) {
        std::cout << "Node " << i << "(";
        for (int j = 0; j < dimensions; ++j) std::cout << nodes[i].coords[j] << ", ";
        std::cout << ") ";
        std::cout << " is connected to: ";
        for (int neighbor : edges[i]) {
            std::cout << neighbor << " ";
        }
        std::cout << std::endl;
    }
}

// Cuenta los componentes conexos del grafo
int RandomGeometricGraph::countConnectedComponents() {
        std::vector<bool> visited(nodes.size(), false);
        int components = 0;

        // Recorremos todos los nodos
        for (size_t i = 0; i < nodes.size(); ++i) {
            if (!visited[i]) {
                // Si no está visitado, iniciamos una nueva búsqueda DFS desde este nodo
                dfs(i, visited);
                components++;  // Contamos un nuevo componente conexo
            }
        }
        return components;
    }

// Realiza percolación eliminando aristas aleatoriamente según una probabilidad
void RandomGeometricGraph::edgePercolation(double probability) {
        std::vector<std::pair<int, int>> edgesToRemove;

        // Recorremos todas las aristas y decidimos si eliminar cada una según la probabilidad
        for (size_t i = 0; i < edges.size(); ++i) {
            for (int neighbor : edges[i]) {
                if (i < neighbor) {
                    double randomValue = static_cast<double>(std::rand()) / RAND_MAX;
                    if (randomValue < probability) {
                        --numEdges;
                        edgesToRemove.push_back({i, neighbor});
                    }
                }
            }
        }

        // Elimina las aristas seleccionadas
        for (const auto& edge : edgesToRemove) {
            removeEdge(edge.first, edge.second);
        }

        //std::cout << "  After edge percolation with probability " << probability * 100 << "%: " << std::endl;
        //printGraph();
        int components = countConnectedComponents();
        //std::cout << "    Number of connected components: " << components << std::endl;
        //std::cout << "    Num de aristas: " << getNumEdges() << std::endl;
    }

int RandomGeometricGraph::getNumEdges() {
    return numEdges;
}


// Genera nodos únicos
void RandomGeometricGraph::generateNodes() {
    std::set<Node> uniqueNodes;  // Usamos un set para garantizar unicidad
    std::srand(std::time(0));

    while (uniqueNodes.size() < static_cast<size_t>(numNodes)) {
        Node newNode;
        for (int i = 0; i < dimensions; ++i) {
            newNode.coords.push_back(static_cast<double>(std::rand()) / RAND_MAX); // Coordenadas aleatorias
        }
        // Solo lo añadimos si no existe otro nodo con las mismas coordenadas
        uniqueNodes.insert(newNode);
    }

    // Pasamos los nodos únicos del set al vector
    nodes.assign(uniqueNodes.begin(), uniqueNodes.end());
}

    // Crea las aristas entre nodos
void RandomGeometricGraph::createEdges() {
    edges.clear();
    edges.resize(nodes.size());
    numEdges = 0;
    for (size_t i = 0; i < nodes.size(); ++i) {
        for (size_t j = i + 1; j < nodes.size(); ++j) {
            if (distance(nodes[i], nodes[j]) <= radius) {
                ++numEdges;
                edges[i].push_back(j);
                edges[j].push_back(i);
            }
        }
    }
}

// Realiza una búsqueda DFS desde un nodo
void RandomGeometricGraph::dfs(int node, std::vector<bool>& visited) {
    std::stack<int> stack;
    stack.push(node);
    visited[node] = true;

    while (!stack.empty()) {
        int current = stack.top();
        stack.pop();

        // Recorremos los vecinos del nodo actual
        for (int neighbor : edges[current]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                stack.push(neighbor);
            }
        }
    }
}

// Elimina una arista entre dos nodos
void RandomGeometricGraph::removeEdge(int node1, int node2) {
    edges[node1].erase(std::remove(edges[node1].begin(), edges[node1].end(), node2), edges[node1].end());
    edges[node2].erase(std::remove(edges[node2].begin(), edges[node2].end(), node1), edges[node2].end());
}