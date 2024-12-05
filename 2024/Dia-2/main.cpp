#include <bits/stdc++.h>

using namespace std;

bool safeReport(const list<int> &rep);
bool toleratedReport(list<int> &rep);

const int INDEF = -1;

int main() {
    ifstream input;
    input.open("input.txt");
    //input.open("test_input.txt");

    /* PARTE 1 y 2*/
    int safe = 0;
    int tolerated = 0;
    for(string line; getline(input,line);) {
        stringstream ss(line);
        //vector<int> report(0);
        list<int> report;

        int level;
        while(ss >> level) {
            report.push_back(level);
        }

        if(safeReport(report)) safe++;
        if(toleratedReport(report)) tolerated++;
    }

    cout << "------- Parte 1 -------" << endl;
    cout << "Safe reports:\t\t" << safe  << endl;
    
    cout << "------- Parte 2 -------" << endl;
    cout << "Tolerated reports:\t" << tolerated  << endl;
    return 0;
}


// Pre: cada reporte tiene al menos dos elementos
bool safeReport(const list<int> & rep) {
    if(rep.size() <= 1) return true;
    
    list<int>::const_iterator itInicio = rep.begin();

    bool creciente = *itInicio - *(++itInicio) < 0;

    // Revisar si la guarda modifica el iterador
    for(list<int>::const_iterator it = rep.begin(); next(it)!=rep.end(); ++it) {

        int actual  = *it;
        int proximo = *next(it);

        // Verifica la cota de distancia
        int diff = abs(actual-proximo);
        if(diff == 0 || diff > 3) return false;

        // Verifica que sea siempre creciente o decreciente
        if(( creciente && (actual - proximo) > 0) ||
           (!creciente && (actual - proximo) < 0)   )
            return false;
    }

    return true;
}



bool toleratedReport(list<int> &rep) {
    int valorActual;
    // Arranca desde el segundo
    for(list<int>::iterator it=(rep.begin()); it!=rep.end(); ++it) {
        valorActual = *it;
        it = rep.erase(it);
        if(safeReport(rep)) {
            rep.insert(it,valorActual);
            return true;
        }
        it = rep.insert(it,valorActual);
    }
    return false;
}