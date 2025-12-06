#include <bits/stdc++.h>

using namespace std;

int main() {
    int MOD = 100;
    int res = 0;

    char dir;
    int cant;
    int pos = 50;
    while(cin >> dir >> cant) {
        if( dir == 'L' ) {
            pos = (MOD + pos - cant) % MOD;
        } else {
            pos = (MOD + pos + cant) % MOD;
        }

        if(pos == 0) res++;
    }


    cout << res << endl;
    return 0;

}
