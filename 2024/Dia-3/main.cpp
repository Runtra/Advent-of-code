// Fuentes:
// Codigo para hallar todas las coincidencias de una regex y extraer resultados
// https://www.geeksforgeeks.org/program-to-find-all-match-of-a-regex-in-a-string/

#include <bits/stdc++.h>

using namespace std;

const int INDEF = -1;

int main() {
    ifstream input;
    input.open("input.txt");
    //input.open("test_input.txt");

    /* PARTE 1 */
    // pattern: "mul([1-9][0-9]*,[1-9][0-9]*)"
    // Extraemos cada resultado
    regex pattern_parte1("mul\\(([1-9][0-9]*),([1-9][0-9]*)\\)");
    
    int res = 0;
    for(string line; getline(input,line);) {
        smatch match;

        while(regex_search(line, match, pattern_parte1)) {
            int primero = stoi(match[1].str());
            int segundo = stoi(match[2].str());
            
            res += primero * segundo;

            line = match.suffix().str();
        }

    }
    cout << "-------------- Parte 1 --------------" << endl;
    cout << "Suma de productos:\t\t" << res << endl << endl;
    
    /* PARTE 2 */
    input.clear();
    input.seekg(0, ios_base::beg);

    regex pattern_parte2("(mul\\(([1-9][0-9]*),([1-9][0-9]*)\\)|do\\(\\)|don't\\(\\))");
    bool enabled = true;
    res = 0;

    for(string line; getline(input,line);) {
        smatch match;

        while(regex_search(line, match, pattern_parte2)) {

            string match_res = match[0].str();
            if(match_res == "do()") {
                enabled = true;
            } else if(match_res == "don't()") {
                enabled = false;
            } else if(enabled) {
            int primero = stoi(match[2].str());
            int segundo = stoi(match[3].str());
            
            res += primero * segundo;
            }

            line = match.suffix().str();
        }
    }

    cout << "-------------- Parte 2 --------------" << endl;
    cout << "Sma de productos(do/don't):\t" << res << endl;
    return 0;
}


