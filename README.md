# Projecte GRAU-A Q2 2024

## Sobre el proyecto

En este trabajo en grupo de la asignatura de Algoritmia en la UPC, desarrollé e implementé en C++ el modelo Barabási-Albert para analizar experimentalmente la percolación en redes complejas. Llevé a cabo estudios sobre la transición de fase en la conectividad del grafo bajo distintos parámetros de percolación, optimizando el rendimiento del análisis y garantizando resultados estadísticamente significativos.

## Documentación

Toda la documentación del proyecto está en: [Proyecto A](Proyecto_A.pdf)

En el documento también salen los integrantes del grupo que ha hecho este proyecto.

## Código

Este programa genera grafos de deferentes modelos y aplica procesos de percolación por aristas y/o por nodos. Los resultados se guardan en archivos CSV.
Desarrollado en C++. 

Para compilar el proyecto ejecutar el comando make en el terminal: 
    make

 Para ejecutar el programa utiliza el comando: 
    ./program

Al ejecutar el programa, hay que introducir el modelo de grafo  a experimentar(introduce 1, 2 o 3) y los parámetros necessarios para crear un grafo de tal modelo. Para cada modelo, hay que introducir: 
- Red cuadrada N x N: el número de N
- RGG: el número de nodos n, el radio r, la dimensión (solo disponemos de la dimensión 2) y el número de repeticiones
- BA: el número de nodos n, la variable m

En cada archivo CSV resultante contiene los siguentes campos: 
- Probabilidad: probabilidad de que un nodo o arista no falle. 
- Componentes_conexas: media de números de componentes conexas después de percolación
- Conectivadad: probabilidad que es el grafo es conexo


