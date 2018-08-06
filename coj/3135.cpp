#include <bits/stdc++.h>

using namespace std;

vector<int> primos;

void criba(int n){
    vector<bool> tmp(n+1, true);
    tmp[1] = false;
    for(int i=2;i*i<=n;i++){
        while(!tmp[i]) i++;
        for(int j=2*i;j<=n;j+=i){
            tmp[j] = false;
        }
    }
    for(int i=1;i<=n;i++){
        if(tmp[i]) primos.push_back(i);
    }
}

int fast_pow(int b, int e){
    int ans = 1;
    while(e > 0){
        if(e%2 == 1){
            ans *= b;
        }
        e = e >> 1;
        b *= b;
    }
    return ans;
}

int fast_pow_mod(int b, int e, int m){
    int ans = 1;
    while(e > 0){
        if(e%2 == 1){
            ans = (ans * b) % m;
        }
        e = e >> 1;
        b = (b * b) % m;
    }
    return ans;
}

map<int, int> factorizar_factorial(int n){
    map<int, int> f;
    for(int i=0;i<primos.size();i++){
        int d = primos[i];
        if(d>n) break;
        int contador = 0;
        int j = 1;
        while(true){
            int tmp = n/fast_pow(d, j);
            contador += tmp;
            if(tmp == 0) break;
            j++;
        }
        f[d] += contador;
    }
    return f;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t, n, maximo;
    maximo = 1;
    cin >> t;
    vector<int> casos(t);
    for(int i=0;i<t;i++){
        cin >> n;
        casos[i] = n;
        if(n > maximo) maximo = n;
    }
    criba(maximo);
    for(int i=0;i<t;i++){
        map<int, int> f = factorizar_factorial(casos[i]);
        int diez = min(f[2], f[5]);
        f[2] -= diez;
        f[5] -= diez;
        int ans = 1;
        for(pair<int, int> j:f){
            ans = (ans * fast_pow_mod(j.first, j.second, 10)) %10;
        }
        cout << ans << endl;
    }
    return 0;
}
