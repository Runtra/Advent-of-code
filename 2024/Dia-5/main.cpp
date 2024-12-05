/*
 * Asumimos, por analizar el input, que el numero de pagina esta entre 0 y 100
 * Supongo tambien que no hay aristas de un nodo a si mismo
 * Por la consigna de la parte dos, entiendo que existe un unico toposort para cada update
 */

// Fuentes
// Regex para split: https://stackoverflow.com/a/10058756

#include <bits/stdc++.h>
#include "../grafos.h"

using namespace std;

void dfs(int actual, int padre);
bool correctOrdering(const vector<int> & ord);
bool esToposort(const vector<int> & ord);
void doToposort(vector<int> & ord);

const int INDEF = -1;
const int MAX_PAGS = 100;

Digrafo dependencias(MAX_PAGS);
vector<bool> enUso(MAX_PAGS,false);
vector<bool> vistos(MAX_PAGS,false);
vector<int>  padres(MAX_PAGS,INDEF);

bool tieneCiclos   = false;
int cantidadVistos = 0;

int main() {
    ifstream input;
    input.open("input.txt");
    //input.open("test_input.txt");
    
    int correctMiddleSum   = 0;
    int incorrectMiddleSum = 0;
    // Armar el grafo de dependencias
    for(string line; getline(input,line);) {
        if(line=="") break;

        stringstream ss(line);
        char barra;
        int x,y;
        while (ss >> x >> barra >> y) {
            dependencias.agregarArista(x,y);
        }
    }


    for(string line; getline(input,line);) {
        vector<int> ord;

        vector<string> tokens;
        regex re("\\d+");

        sregex_token_iterator begin(line.begin(),line.end(),re),end;

        copy(begin,end,back_inserter(tokens));

        ord.resize(tokens.size());
        for(int i=0; i<(int)ord.size(); i++) {
            ord[i] = stoi(tokens[i]);
        }

        if(esToposort(ord)) {
            correctMiddleSum += ord[ord.size()/2];
        } else {
            doToposort(ord);
            incorrectMiddleSum += ord[ord.size()/2];
        }
    }

    cout << "-------------- Parte 1 --------------" << endl;
    cout << "Reportes correctos:\t" << correctMiddleSum << endl << endl;
    cout << "-------------- Parte 2 --------------" << endl;
    cout << "Reportes incorrectos:\t" << incorrectMiddleSum << endl << endl;
    return 0;
}

stack<int> pilaToposort;
// Asume que este orden si o si tiene un solo toposort posible
void doToposort(vector<int> & ord) {
    for(auto pagina : ord) {
        enUso[pagina] = true;
    }
    pilaToposort = stack<int>();

    for(int pagina : ord) {
        if(vistos[pagina]) continue;

        padres[pagina] = pagina;

        dfs(pagina,pagina); // Debe apilar en pilaToposort
    }

    // ord_out = reverse(orden dfs)
    for(int i=0; i<(int)ord.size(); i++) {
        ord[i] = pilaToposort.top();
        pilaToposort.pop();
    }

    assert(pilaToposort.empty());

    for(auto pagina : ord) {
        enUso[pagina]  = false;
        vistos[pagina] = false;
    }
}

void dfs(int actual, int padre) {
    vistos[actual] = true;
    //cantidadVistos += 1;

    for(auto vecino : dependencias.vecindarioDeSalida(actual)) {
        if(!enUso[vecino]) continue;
        if(vecino == padre) continue;

        if(vistos[vecino]) continue;

        padres[vecino] = actual;
        dfs(vecino,actual);
    }
    pilaToposort.push(actual);
}


// Idea:
//  - Es un toposort si y solo si al sacar los nodos en el orden inverso siempre
//    cada nodo es una hoja
bool esToposort(const vector<int> & ord) {
    for(auto pagina : ord) {
        enUso[pagina] = true;
    }
    bool res = true;

    for(int i=ord.size()-1; i>=0; i--) {
        unordered_set<int> salidas = dependencias.vecindarioDeSalida(ord[i]);
        for(int vecino : salidas) {
            if(enUso[vecino]) {
                res = false;
                break;
            }
        }
        if(!res) break;

        enUso[ord[i]] = false;

    }
    // Deberia ser necesario??
    // Entiendo que si, pues elegimos cortar antes el ciclo
    for(auto pagina : ord) {
        enUso[pagina]  = false;
    }
    
    return res;
}