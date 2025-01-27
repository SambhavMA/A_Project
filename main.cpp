/**
 * main.cpp
 * Descripción: dado un modelo, crea un grafo de tal modelo con los parámetros dados 
 * y aplicar percolaciones por aristas y/o por nodos. Escribe el resultado de 
 * percolación en archivos csv  
 */

#include "Graph.h"
#include "RGGraph.cpp"
#include <unistd.h>
#include <fstream>

void modeloGrid(){
    cout << "El número de N para crear una red cuadrada NxN: ";
    int n;
    cin >> n; 
    grid g(n); // crear una red cuadrada de n por n

    cout << "Grafo generado. Percolación en proceso." << endl;

    //Crear archivos de salida
    string nameN = "GridNodos" + to_string(n) + ".csv";
    string nameE = "GridEdges" + to_string(n) + ".csv";
    ofstream archivoN(nameN); 
    ofstream archivoE(nameE); 
    archivoN << "Probabilidad,Componestes_conexas, conectividad \n";
    archivoE << "Probabilidad,Componestes_conexas, conectividad \n";

    //configurar parametros
    int repeticiones = 100;
    float steps = 0.01;
    int rang = 1 /steps;
    
    double q; //la probabilidad de que no falla

    for (int j = 0; j <= rang; ++j){
        q = j*steps;

        int sumN, connectedN, sumE, connectedE;
        sumN = connectedN = sumE = connectedE = 0;

        for (int i = 0; i < repeticiones; ++i){
            g.percolateNodes(q);
            sumN += g.getCount();
            connectedN += (g.getCount() == 1? 1 : 0);

            g.percolateEdges(q);
            sumE += g.getCount();
            connectedE += (g.getCount() == 1? 1 : 0);
        }
        
        archivoE << q << ',' << double(sumE)/repeticiones << ',' <<  double(connectedE)/repeticiones << "\n";
        archivoN << q << ',' << double(sumN)/repeticiones << ',' <<  double(connectedN)/repeticiones << "\n";
    }
    archivoE.close();
    archivoN.close();
    cout << "Percolaciones finalizadas y resultados guardados en: " << nameE << " " << nameN << endl;
}

void modeloRGG(){
    string name = "RGG.csv";
    ofstream archivo(name); 
    archivo << "Probabilidad,Componestes_conexas, conectividad \n";

    srand(static_cast<unsigned>(time(0)));
    int numNod;
    double rad;
    int dim;
    int repeticiones;
    double q = 0.01;

    std::cout << "Introduce el numero de nodos: ";
    std::cin >> numNod;
    std::cout << "Introduce el radio: ";
    std::cin >> rad;
    std::cout << "Introduce las dimensions: ";
    std::cin >> dim;
    std::cout << "Introduce el numero de repeticiones: ";
    std::cin >> repeticiones;

    while (q < 1) {
        double numComp = 0;
        double conect = 0;

        for (int i = 0; i < repeticiones; ++i) {
            RandomGeometricGraph rgg(numNod, rad, dim);
            int k = 0;
            while (rgg.countConnectedComponents() != 1) {
                if (k < 20) ++k;
                else {
                    std::cout << "Despues de 20 intentos, no se ha podido generar un grafo conexo." << std::endl;
                    return;
                }
                rgg = RandomGeometricGraph(numNod, rad, dim);
            }
            RandomGeometricGraph aux = rgg;
            aux.edgePercolation(q);
            int count = aux.countConnectedComponents();
            if (count > 1) ++conect;
            numComp += (double)count;

        }

        numComp /= repeticiones;
        conect /= repeticiones;

        archivo << q << " " << numComp << " " << conect << "\n";
        q += 0.01;
    }

    archivo.close();
    cout << "Percolaciones finalizadas y resultados guardados en: " << name << endl;
}

void modeloBA(){
    int repeticiones = 10;
    float steps = 0.01;
    int rang = 1 /steps;

   
    cout << "Define la n del grafo: ";
    
    int n; cin >> n;

    cout << "Define la m del grafo: ";

    int m; cin >> m;

    double p;

    std::ofstream archivo("BA_datos.csv"); 
    //std::ofstream archivo("BA_Nodos.csv");  // Crea o abre el archivo CSV
    
        
    archivo << endl;
    archivo << "N: " << n << ";" <<"M: " << m << endl; //';' sirve para escribir en 2 columnas distintas
    archivo << "percolacion aristas" << endl << "p;|C.C|" << endl;
    for (int j = 0; j <= rang; ++j) {
                
        p = j*steps;   
        double sum_a = 0; //calculamos la media

        for (int i1 = 0; i1 < repeticiones; ++i1){//generamos varios grafos aleatorios para la misma probabilidad y los percolamos
             
            BA g_aristas(n,m);
            g_aristas.percolateEdges(p);
            sum_a += g_aristas.getCount();        
        }

        archivo << p << ';' << sum_a/repeticiones << endl; //ponemos la media de las repeticiones hechas
    }
            
    archivo << "percolacion nodos" << endl << "p;|C.C|" << endl;

    for (int j = 0; j <= rang; ++j) {
        p = j*steps;
        double sum_n = 0;

        for (int i2 = 0; i2 < repeticiones; ++i2){ 
            BA g_nodos(n,m);
            g_nodos.percolateNodes(p);
            sum_n += g_nodos.getCount();          
        }

        archivo << p << ';' << sum_n/repeticiones << endl;
    }

    archivo.close();

    cout << "Percolaciones finalizadas y resultados guardados en: BA_datos.csv" << endl; ;
}

int main(){
    cout << "Selecciona el modelo: \n 1.Red cuadrada\n 2.RGG\n 3.BA\n";
    int modelo; 
    cin >> modelo; 

    switch (modelo){
    case 1: 
        modeloGrid();
        break;
    case 2: 
        modeloRGG();
        break;
    case 3: 
        modeloBA();
        break;
    default: 
        cout << "Modelo no existe" << endl;
    }
}