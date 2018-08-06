#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long int ull;

map<ull, int> factorizar(ull n){
    map<ull, int> factores;
    if(n == 1 || n == 0) return factores;
    ull d = 2;
    while(d <= sqrt(n)){
        if(n%d == 0){
            factores[d]++;
            n /= d;
        }else{
            d++;
        }
    }
    factores[n]++;
    return factores;
}

int main()
{
    ios_base::sync_with_stdio(false);
    string linea;
    while(getline(cin, linea)){
        // n!/m
        ull n, m;
        stringstream s(linea);
        s >> n >> m;
        map<ull, int> f = factorizar(m);

        for(pair<ull, int> p: f){
            cout << p.first << " " << p.second << endl;
        }
    }
    return 0;
}
