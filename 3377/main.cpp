#include <bits/stdc++.h>

using namespace std;
typedef long long int ull;

vector<ull> primos;

void criba(ull n){
    vector<bool> tmp(n+1, true);
    tmp[1] = false;
    ull bound = sqrt(n);
    for(ull i=2;i<=bound;i++){
        while(!tmp[i]) i++;
        for(ull j=2*i;j<=n;j+=i){
            tmp[j] = false;
        }
    }
    for(ull i=1;i<=n;i++){
        if(tmp[i]) primos.push_back(i);
    }
}

ull factorizar(ull n, ull m, vector<ull> *f){
    ull i = 0;
    for(;i<primos.size();i++){
        ull d = primos[i];
        if(d>n) break;
        ull contador = 0;
        while(n%d == 0){
            contador++;
            n /= d;
        }
        (*f)[i] += contador*m;
    }
    return i-1;
}

int main()
{
    vector<bool> ocupados(300, false);
    vector<ull> info(300, 0);
    criba(400000);
    for(ull i=1;i<=400000;i++){
        ull tmp = 1;
        vector<ull> f(primos.size(), 0);
        ull max_p = factorizar(i, 1, &f);
        for(int j=0;j<=max_p;j++){
            if(f[j]>0){
                tmp *= f[j]+1;
            }
        }
        if(!ocupados[tmp]){
            info[tmp] = i;
            ocupados[tmp] = true;
        }
    }
    for(ull i=1;i<300;i++) cout << i << " divisores: " << info[i] << endl;
    return 0;
}
