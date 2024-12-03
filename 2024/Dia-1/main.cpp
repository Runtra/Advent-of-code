#include <bits/stdc++.h>

using namespace std;

const int INDEF = -1;

int main() {
    ifstream input;
    input.open("input.txt");
    //input.open("test_input.txt");

    vector<int> izq; //(1000,INDEF);
    vector<int> der; //(1000,INDEF);

    while(input.good()) {
        int valIzq, valDer;
        input >> valIzq >> valDer;
        izq.push_back(valIzq);
        der.push_back(valDer);
    }
    
    sort(izq.begin(),izq.end());
    sort(der.begin(),der.end());


    /* PARTE 1 */
    int totalDistance = 0;
    for(int i=0; i<izq.size(); i++) {
        totalDistance += abs(izq[i]-der[i]);
    }
    cout << "Parte 1\nDistance:\t" << totalDistance << endl << endl;


    /* PARTE 2 */
    int similarity = 0;
    int ultimoDerIdx = 0;
    for(int i=0; i<izq.size(); i++) {
        // Calcular cuantas apariciones hay en la lista de la derecha
        int cantidad = 0;
        for(int j=ultimoDerIdx; j<der.size(); j++) {
            while(izq[i] == der[j]) {
                cantidad++;
                j++;
            }

            ultimoDerIdx = j;
            if(izq[i]<der[j]) break;
        }
        
        similarity += izq[i]*cantidad;

        // Avanzar el indice hasta el proximo numero distinto
        int idx = i;
        while(izq[i] == izq[idx]) {
            idx++;
        }
        idx--;
        i = idx;
    }

    cout << "Parte 2\nSimilarity:\t" << similarity << endl;

}