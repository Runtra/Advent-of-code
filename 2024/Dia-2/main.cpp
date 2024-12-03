#include <bits/stdc++.h>

using namespace std;

bool safeReport(const vector<int> &report);

int main() {
    ifstream input;
    input.open("input.txt");
    //input.open("test_input.txt");

    /* PARTE 1 */
    int res = 0;
    for(string line; getline(input,line);) {
        stringstream ss(line);
        vector<int> report(0);

        int level;
        while(ss >> level) {
            report.push_back(level);
        }

        if(safeReport(report)) res++;
    }

    cout << "------- Parte 1 -------" << endl;
    cout << "Safe reports:\t" << res  << endl;

    /* PARTE 2 */
    input.seekg(ios_base::beg);


}


// Pre: cada reporte tiene al menos dos elementos
bool safeReport(const vector<int> &rep) {
    if(rep.size() <= 1) return true;

    bool creciente = (rep[0] - rep[1]) < 0;
    bool removio   = false;
    for(int i=0; i<rep.size()-1; i++) {


        
        // Verifica la cota de distancia
        int diff = abs(rep[i]-rep[i+1]);
        if(diff == 0 || diff > 3) return false;

        // Verifica que sea siempre creciente o decreciente
        if(( creciente && (rep[i] - rep[i+1]) > 0) ||
           (!creciente && (rep[i] - rep[i+1]) < 0)   )
            return false;
    }

    return true;
}