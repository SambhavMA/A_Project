
#include "Graph.h"

random_device myRandomDevice;
uniform_real_distribution<> Uniforme(0.0, 1.0);
unsigned seed = myRandomDevice();
default_random_engine RNG(seed);

double GetRandomProb(){
    return Uniforme(RNG);
}

// Función para generar m numeros aleatorios enteros en el rango [0, n]
vector<int> GetRandomNumbers(int m, int n) {
    uniform_int_distribution<int> distribucion(0, n); 
    vector<int> numeros(m);                           

    for (int i = 0; i < m; ++i) {
        numeros[i] = distribucion(RNG);               
    }

    return numeros;                                  
}

// Función para generar un numero aleatorio entero en el rango [n0, n]
int GetRandomNumber(int n0,int n) {
    uniform_int_distribution<int> distribucion(n0, n); 
    return distribucion(RNG);                                  
}

Graph::Graph(int n){
    vertices = n;
    adj = unordered_map<int, vector<int>> (n);
}

bool Graph::connected(int u, int v) {
    for (int i = 0; i < adj[u].size(); ++i) {
        if (adj[u][i] == v) return true;
    }
    return false;
}

void Graph::addEdge(int u, int v) {
    adj[u].push_back(v); 
    adj[v].push_back(u);
}

void Graph::percolateEdges(double q){
    uf = UF(vertices);
    for (const auto& arista : adj){
        int u = arista.first;
        for (int v : arista.second) {
            if (u < v and GetRandomProb() <= q) uf.unite (u, v);
        }
    }
}

void Graph::percolateNodes(double q){
    uf = UF(vertices);
    vector<bool> nodesFailed(vertices, false); //Indica si hay que eliminar el nodo o no

    int count = 0; //numero de nodos eliminados

    for (const auto& arista : adj){
        int u = arista.first;
        if (GetRandomProb() >= q) {
            ++count;
            nodesFailed[u] = true;
        }
    }

    for (const auto& arista : adj){
        int u = arista.first;
        for (int v : arista.second) {
            if (not nodesFailed[u] && not nodesFailed[v])  uf.unite(u,v);
        }
    }

    uf.updateCount(count);
}

int Graph::getCount(){
    return uf.getCount();
}

grid::grid(int n): Graph(n*n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int u = i*n + j;
            if (i + 1 < n) addEdge(u, u+n); // Conexión hacia abajo
            if (j + 1 < n) addEdge(u, u+1); // Conexión hacia la derecha
        }
    }
}

//PRE: n > m y 1 <= m <= 6
BA::BA (int n, int m): Graph(n) {

    //generamos un grafo inicial aleatorio de tamaño m0, m0 >= m
    int m0;
    if (m > 1) m0 = GetRandomNumber(m, 5); //generara un grafo aleatorio de tamaño m a 6 (m0 <= m)
    else m0 = GetRandomNumber(2, 5);
    vector <int> degree_list; //vector con los nodos repetidos tantas veces como su grado
    //este vector lo usaremos para ahorrarnos calcular probabilidades aleatorias para cada nueva arista que añadamos

    for (int i = 0; i < m0-1; ++i) {
        bool edgeadded = false; //como mínimo cada nodo ha de tener un vértice! segun el modelo
        while (not edgeadded) {
            for (int j = i + 1; j < m0; ++j) {
                double rand = GetRandomProb();
                if (rand <= 0.5) {
                    addEdge(i,j);
                    degree_list.push_back(i); degree_list.push_back(j);
                    edgeadded = true;
                }
            }
            
        }
    }
    if (m0 > 1 and adj[m0-1].size() == 0) { //miramos si el ultimo vertice no tiene aristas, si no las tiene le añadimos una aleatoria
        bool edgeadded = false; 
        while (not edgeadded) {
            for (int j = 0; j < m0-1; ++j) {
                double rand = GetRandomProb();
                if (rand <= 0.5) {
                    addEdge(m0-1,j);
                    degree_list.push_back(m0-1); degree_list.push_back(j);
                    edgeadded = true;
                }
            }
        }
    }

   //empezamos añadiendo nodos al grafo hasta llegar a n, los nuevos nodos tendrán m aristas y tienen
   //más posibilidades de conectarse a vertices con mayor grado, siguiendo el modelo BA    

    for (int i = m0; i < n; ++i) {
        vector<int> random_nums = GetRandomNumbers(m, degree_list.size()-1);
        for (int j = 0; j < m; ++j) {
            int rnd_j = random_nums[j];            
            
            if (not connected(i, degree_list[rnd_j]) and i != degree_list[rnd_j]) {
                addEdge(i, degree_list[rnd_j]); degree_list.push_back(i); degree_list.push_back(degree_list[rnd_j]);  //i es el nuevo nodo que conectamos con m nodos elegidos por el modelo
            }
            else { //buscamos otro vetice random al que conectar nuestro vertice
                int rnd = GetRandomNumber(0,degree_list.size()-1);
                while (connected (i, degree_list[rnd]) or i == degree_list[rnd]) { //como que el grado de los vertices es >= 1 y m <= m0 no habrá bucle infinito
                    rnd = GetRandomNumber(0,degree_list.size()-1);                    
                 }
                addEdge(i, degree_list[rnd]); degree_list.push_back(i); degree_list.push_back(degree_list[rnd]); 
            }
            
        }

    }
}

