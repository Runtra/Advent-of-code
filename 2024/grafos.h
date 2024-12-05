#include <bits/stdc++.h>

using namespace std;



// Hacer grafo arbol (padres e hijos)
// Hacer digrafos


typedef struct Grafo {
    using vertice = int;
    using arista  = pair<int,int>;

    vector<unordered_set<int>> adyacencias;
    int cantidadVertices;
    int cantidadAristas;

    Grafo(int n, vector<arista> const & listaAristas=vector<arista>(0)) {
        cantidadVertices = n;
        adyacencias.resize(n); // Capaz deberia ser un assign

        cantidadAristas = listaAristas.size();
        for(auto [v,w] : listaAristas) {
            agregarArista(v,w);
        }
    }


    // O(1) esperado
    // O(n) peorsito
    void agregarArista(vertice v, vertice w) {
        assert( 0<=v && 0 <= w);

        if(max(v,w) > cantidadVertices) {
            cantidadVertices = max(v,w);
            adyacencias.resize(cantidadVertices);
        }
        adyacencias[v].insert(w);
        adyacencias[w].insert(v);
        cantidadAristas += 1;
    }

    // pre: n>0
    // O(n) esperado
    // O(n + |adyacencias|) peorsito
    void agregarNVertices(int n=1) {
        assert(n>0);
        adyacencias.resize(cantidadVertices+n);
        cantidadVertices += n;
    }

    // pre: v es vertice de el grafo
    // O(1)
    unordered_set<int> vecindario(vertice v) {
        assert(0<=v && v<cantidadVertices);
        return adyacencias[v];
    }

    void borrarAdyacencias(){
        cantidadAristas = 0;
        adyacencias.assign(cantidadVertices, unordered_set<int>({}));
    }

    vector<pair<int,int>> aListaDeAristas() {
        vector<pair<int,int>> res(0);
        for(int i=0; i<cantidadVertices; i++) {
            for(auto v : vecindario(i)) {
                if(v>i) res.push_back({i,v});
            }
        }
        return res;
    }
} Grafo;


typedef struct Digrafo {
    using vertice = int;
    using arista  = pair<int,int>;

    vector<unordered_set<int>> salidas;
    vector<unordered_set<int>> entradas;

    int cantidadVertices;
    int cantidadAristas;

    // Convencion: el par ordenado (v,w) indica la arista v->w 
    Digrafo(int n, vector<arista> const & listaAristas=vector<arista>(0)) {
        cantidadVertices = n;
        salidas.resize(n);
        entradas.resize(n);

        cantidadAristas = listaAristas.size();
        for(auto [v,w] : listaAristas) {
            agregarArista(v,w);
        }
    }


    // O(1) esperado
    // O(n) peorsito
    void agregarArista(vertice v, vertice w) {
        assert( 0<=v && 0 <= w);

        if(max(v,w) > cantidadVertices) {
            cantidadVertices = max(v,w);
            salidas.resize(cantidadVertices);
            entradas.resize(cantidadVertices);
        }
        salidas[v].insert(w);
        entradas[w].insert(v);
        cantidadAristas += 1;
    }

    // pre: n>0
    // O(n) esperado
    // O(n + |adyacencias|) peorsito
    void agregarNVertices(int n=1) {
        assert(n>0);
        salidas.resize(cantidadVertices+n);
        entradas.resize(cantidadVertices+n);

        cantidadVertices += n;
    }

    // pre: v es vertice de el grafo
    // O(1)
    unordered_set<int> vecindarioDeSalida(vertice v) {
        assert(0<=v && v<cantidadVertices);
        return salidas[v];
    }

    // pre: v es vertice de el grafo
    // O(1)
    unordered_set<int> vecindarioDeEntrada(vertice v) {
        assert(0<=v && v<cantidadVertices);
        return entradas[v];
    }
} Digrafo;