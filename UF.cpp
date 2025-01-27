#include <vector>
#include <iostream>
using namespace std;

class UF { //weighted quick-union with path compression
private:
    vector<int> id;  // raíz de cada componente conexo
    vector<int> sz;  // tamaño del componente conexo
    int count;       // números de componentes conexos

    int find(int p) {
        while (p != id[p]) {
            id[p] = id[id[p]]; //path compression
            p = id[p];
        }
        return p;
    }

public:
    UF(){
    }
    
    UF(int N) { 
        count = N;
        id = vector<int>(N);
        sz = vector<int>(N);

        for (int i = 0; i < N; i++) {
            id[i] = i;
            sz[i] = 1;
        }
    }

    int getCount(){
        return count;
    }

    bool connected(int p, int q) {
        return find(p) == find(q);
    }

    void unite(int p, int q) {
        int i = find(p);
        int j = find(q);
        if (i == j) return;
        
        if (sz[i] < sz[j]) {
            id[i] = j;
            sz[j] += sz[i];
        } else {
            id[j] = i;
            sz[i] += sz[j];
        }
        count--;
    }

    void updateCount(int c){
        count -= c;
    }
    
};