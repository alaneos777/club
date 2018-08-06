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

ull fast_pow(ull b, ull e){
    ull ans = 1;
    while(e > 0){
        if(e%2 == 1){
            ans *= b;
        }
        e = e >> 1;
        b *= b;
    }
    return ans;
}

ull fast_pow_mod(ull b, ull e, ull m){
    ull ans = 1;
    while(e > 0){
        if(e%2 == 1){
            ans = (ans * b) % m;
        }
        e = e >> 1;
        b = (b * b) % m;
    }
    return ans;
}

ull factorizar_factorial(ull n, ull m, vector<ull> *f){
    ull i=0;
    for(;i<primos.size();i++){
        ull d = primos[i];
        if(d>n) break;
        ull contador = 0;
        ull j = 1;
        while(true){
            ull tmp = n/fast_pow(d, j);
            if(tmp == 0) break;
            contador += tmp;
            j++;
        }
        (*f)[i] += contador*m;
    }
    return i-1;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ull t;
    cin >> t;
    ull maximo = 0;
    vector< vector<ull> > entrada(t);
    string cadena;
    for(ull i=0;i<t;i++){
        cin >> cadena;
        ull n = cadena.size();
        vector<ull> chars(26, 0);
        for(ull j=0;j<n;j++){
            chars[cadena[j]-97]++;
        }
        vector<ull> tmp = {n};
        for(ull p:chars){
            if(p > 1){
                tmp.push_back(p);
            }
        }
        if(n > maximo) maximo = n;
        entrada[i] = tmp;
    }
    criba(maximo);
    for(ull i=0;i<t;i++){
        vector<ull> f(primos.size()+3, 0);
        ull max_primo = factorizar_factorial(entrada[i][0], 1, &f);
        for(ull j=1;j<entrada[i].size();j++){
            factorizar_factorial(entrada[i][j], -1, &f);
        }
        ull diez = min(f[0], f[2]);
        f[0] -= diez;
        f[2] -= diez;
        ull ans = 1;
        for(ull j=0;j<=max_primo;j++){
            ans = (ans * fast_pow_mod(primos[j], f[j], 10)) %10;
        }
        cout << ans << endl;
    }
    return 0;
}
