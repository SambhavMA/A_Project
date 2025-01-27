/**
 * Clase: Graph
 * Descipción: Implementa la estructura de grafo utilizando lista de adyacencias 
 * Dispone de operaciones de constructora de cada tipo de grafos que vamos que experimentar
 * y las operaciones de percolación por aristas y por nodos.  
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <random>
#include <algorithm>
#include <numeric>
#include "UF.cpp"
#include <set>
using namespace std;

extern random_device myRandomDevice;
extern uniform_real_distribution<> Uniforme;
extern unsigned seed;
extern default_random_engine RNG;


double GetRandomProb();

// Función para generar m numeros aleatorios enteros en el rango [0, n]
vector<int> GetRandomNumbers(int m, int n);

// Función para generar un numero aleatorio entero en el rango [N0, n]
int GetRandomNumber(int n0,int n); 

class Graph {
protected:
    int vertices;
    unordered_map<int, vector<int>> adj;
    UF uf;

public:
    //Constructora de un grafo de n vertices
    Graph(int n);

    // Agregar una arista al grafo para constuir un grafo en lista de adyacencias
    void addEdge(int u, int v);

    // retorna si 2 vertices son connexos o no
    bool connected(int u, int v);

    //Percolación por aristas con probabilidad q, donde q es la 
    //probabilidad de que no falla una arista
    void percolateEdges(double q);

    //Percolación por vertices con probabilidad q, donde q es la 
    //probabilidad de que no falla un nodo
    void percolateNodes(double q);

    //Devuelve el número de componentes conexos después de percolación
    int getCount();
};


// Subclase para una red cuadrada
class grid : public Graph {
public:
    //Constructora de una red cuadrada con n*n vertices
    grid(int n);
};

// Subclase para el modelo aleatorio de Barabási-Albert
class BA : public Graph {
public:
    BA(int n, int m);
}; 

#endif // GRAPH_H