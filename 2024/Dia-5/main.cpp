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
    
    // Armar el grafo de dependencias
    for(string line; getline(input,line);) {
        if(line=="") break;

        stringstream ss(line);
        char barra;
        int x,y;
        while (ss >> x >> barra >> y) {
            dependencias.agregarArista(x,y);
            // cout << x << "|" << y << endl;
        }
    }
    //regex regPattern("(([0-9])*,)+([0-9])*");
    //regex regPattern("([0-9]*),|([0-9]*)");
    //regex regPattern("mul\\(([1-9][0-9]*),([1-9][0-9]*)\\)");

    int res = 0;
    for(string line; getline(input,line);) {
        //smatch match;
        vector<int> ord;
        //while(regex_search(line, match, regPattern)) {
        //    //int primero = stoi(match[1].str());
        //    //int segundo = stoi(match[2].str());
        //    
        //
        //    line = match.suffix().str();
        //}
        //ord.resize(match.size()-1);
        //for(int i=1; i<match.size(); i++){
        //    ord[i-1] = stoi(match[i]);
        //}

        vector<string> tokens;
        regex re("\\d+");

        sregex_token_iterator begin(line.begin(),line.end(),re),end;

        copy(begin,end,back_inserter(tokens));

        ord.resize(tokens.size());
        for(int i=0; i<ord.size(); i++) {
            ord[i] = stoi(tokens[i]);
        }

        if(esToposort(ord)) {
            res += ord[ord.size()/2];
        }
    }

    cout << res << endl;
    return 0;
}

bool correctOrdering(const vector<int> & ord) {
    for(auto pagina : ord) {
        enUso[pagina] = true;
    }
    tieneCiclos = false;
    cantidadVistos = 0;

    int raiz = ord[0];
    padres[raiz] = raiz;

    dfs(raiz,raiz);

    for(auto pagina : ord) {
        enUso[pagina]  = false;
        vistos[pagina] = false;
    }
    return !tieneCiclos && cantidadVistos == ord.size();
}

void dfs(int actual, int padre) {
/*     if(padres[actual]==actual) { // Hace falta?
        vistos[actual] = true;
    } */

    vistos[actual] = true;
    cantidadVistos += 1;

    for(auto vecino : dependencias.vecindarioDeSalida(actual)) {
        if(!enUso[vecino]) continue;
        if(vecino == padre) continue;

        if(vistos[vecino]) {
            unordered_set<int> salidas = dependencias.vecindarioDeSalida(vecino);
            if(salidas.find(actual) != salidas.end()) {
                tieneCiclos = true;
                return;
            } else {
                continue;
            }
        }

        padres[vecino] = actual;
        dfs(vecino,actual);
    }
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