// Fuentes:
// Codigo para hallar todas las coincidencias de una regex y extraer resultados
// https://www.geeksforgeeks.org/program-to-find-all-match-of-a-regex-in-a-string/

/*
 * Esta hecho re bruto mal. Hace que sea una paja la parte 2
 *
 * 
 */
#include <bits/stdc++.h>

using namespace std;

int contarXMAS(int x,int y);
int contarCrossMAS(int x, int y);

inline bool esXMAS(const string palabra);


const int INDEF = -1;

vector<vector<char>> matriz;
int height;
int width;

int main() {
    ifstream input;
    input.open("input.txt");
    //input.open("test_input.txt");
    
    int idx = 0;
    for(string line; getline(input,line);) {
        matriz.push_back(vector<char>(0));

        char c;
        stringstream ss(line);
        while(ss >> c) {
            matriz[idx].push_back(c);
        }
        
        idx++;
    }
    
    height = matriz.size();
    width  = matriz[0].size();


    int XMAS = 0;
    int cross_MAS = 0;
    for(int i = 0; i<height; i++) {
        for(int j = 0; j<width; j++) {
            XMAS += contarXMAS(j,i);
            cross_MAS += contarCrossMAS(j,i);
        }
    }
    
    cout << "-------------- Parte 1 --------------" << endl;
    cout << "Cantidad XMAS:\t" << XMAS << endl << endl;
    cout << "-------------- Parte 2 --------------" << endl;
    cout << "Cantidad X-MAS:\t" << cross_MAS << endl << endl;

    return 0;
}


// Cuando aprenda a codear hago bien este ejercicio
int contarXMAS(int x,int y) {
    string palabra = "    "; // Ya la creo de tamaño 4 para poder indexarla
    int res = 0;

    palabra[0] = matriz[y][x];

    // Horizontal a la derecha
    if(x<=width-4) {
        palabra[1] = matriz[ y ][x+1];
        palabra[2] = matriz[ y ][x+2];
        palabra[3] = matriz[ y ][x+3];
        res += esXMAS(palabra);
    }

    // Si estoy en las ultimas 3 lineas, solo puedo contar en horizontal
    if(y>height-4) return res;

    // Diagonal abajo izquierda
    if(x>=3) {
        palabra[1] = matriz[y+1][x-1];
        palabra[2] = matriz[y+2][x-2];
        palabra[3] = matriz[y+3][x-3];
        res += esXMAS(palabra);
    }
    // Diagonal abajo derecha
    if(x<=width-4) {
        palabra[1] = matriz[y+1][x+1];
        palabra[2] = matriz[y+2][x+2];
        palabra[3] = matriz[y+3][x+3];
        res += esXMAS(palabra);
    }
    // Vertical abajo
    palabra[1] = matriz[y+1][ x ];
    palabra[2] = matriz[y+2][ x ];
    palabra[3] = matriz[y+3][ x ];
    res += esXMAS(palabra);

    return res;
}

inline bool esXMAS(const string palabra) {
    return palabra == "XMAS" || palabra == "SAMX";
}


int contarCrossMAS(int x, int y) {
    if(matriz[y][x] != 'A') return 0;

    if(x == width -1 || x == 0) return 0;
    if(y == height-1 || y == 0) return 0;

    if( matriz[y-1][x-1] == 'X' ||
        matriz[y+1][x-1] == 'X' ||
        matriz[y-1][x+1] == 'X' ||
        matriz[y+1][x+1] == 'X')
        return 0;

    if( matriz[y-1][x-1] == 'A' ||
        matriz[y+1][x-1] == 'A' ||
        matriz[y-1][x+1] == 'A' ||
        matriz[y+1][x+1] == 'A')
        return 0;

    /* Formato:
     *  X . X
     *  . A .
     *  Y . Y
     */
    if( matriz[y-1][x-1] == matriz[y-1][x+1] &&
        matriz[y+1][x-1] == matriz[y+1][x+1] &&
        matriz[y-1][x-1] != matriz[y+1][x-1]) 
        return 1;


    /* Formato:
     *  Y . X
     *  . A .
     *  Y . X
     */
    if( matriz[y-1][x-1] == matriz[y+1][x-1] &&
        matriz[y-1][x+1] == matriz[y+1][x+1] &&
        matriz[y-1][x-1] != matriz[y-1][x+1])
        return 1;

    return 0;
}



