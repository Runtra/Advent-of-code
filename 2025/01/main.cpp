#include <bits/stdc++.h>
#include <ostream>

using namespace std;

int main() {
    const int MOD = 100;
    const int INDEF = -1;

    // Pre: asume que x ya esta en el rango
    auto sumaMod = [MOD](int x, int y) {
        return (MOD * abs(y) + x + y) % MOD;
    };

    int res = 0;
    int pos = 50;

    char dir;
    int cant;
    int resto;
    int last = INDEF;
    while(cin >> dir >> cant) {
        res += cant / MOD;

        resto = cant % MOD;
        last = pos;
        if( dir == 'L' ) {
            pos = sumaMod(pos,-resto);
            
            if(resto != 0)
            if((pos >= last && last != 0) || pos == 0 )
                res++;

        } else if( dir == 'R' ) {
            pos = sumaMod(pos,resto);

            if(resto != 0)
            if((pos <= last && last != 0) || pos == 0 )
                res++;
        }

    }

    cout << res << endl;
    return 0;

}
