#ifndef RGGRAPH_H
#define RGGRAPH_H

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <set>
#include <stack>
#include <algorithm>

// Estructura del nodo con coordenadas en cualquier dimensión
struct Node {
    std::vector<double> coords; // Coordenadas en cualquier dimensión

    // Sobrecarga del operador < para comparar nodos en un set
    bool operator<(const Node& other) const {
        return coords < other.coords;
    }
};

class RandomGeometricGraph {
public:
    RandomGeometricGraph(int numNodes, double initialRadius, int dimensions);

    // Imprime los nodos y sus conexiones
    void printGraph() const ;

    // Cuenta los componentes conexos del grafo
    int countConnectedComponents();

    // Realiza percolación eliminando aristas aleatoriamente según una probabilidad
    void edgePercolation(double probability);

    int getNumEdges();

private:
    int numNodes;
    int numEdges;
    double radius;
    int dimensions;
    std::vector<Node> nodes;
    std::vector<std::vector<int>> edges;

    // Genera nodos únicos
    void generateNodes();

    // Crea las aristas entre nodos
    void createEdges();

    // Realiza una búsqueda DFS desde un nodo
    void dfs(int node, std::vector<bool>& visited);

    // Elimina una arista entre dos nodos
    void removeEdge(int node1, int node2);
};


#endif // RGGRAPH_H