#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;

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

ull fast_pow(ull b, ull e){
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
    int m = 1000000007;
    for(int i=0;i<t;i++){
        ull ans1 = 1, ans2 = 1;
        map<int, int> f = factorizar_factorial(casos[i]);
        for(pair<int, int> j:f){
            ull tmp = 0, tmp2 = 1;
            for(int k=0;k<=j.second;k++){
                tmp = (tmp + tmp2) % m;
                tmp2 = (tmp2 * j.first) % m;
            }
            ans1 = (ans1 * tmp) % m;
            ans2 = (ans2 * fast_pow_mod(j.first, j.second, m)) % m;
        }
        int ans = 0;
        if(ans1 >= ans2){
            ans = (ans1 - ans2) % m;
        }else{
            ans = m - (ans2 - ans1) % m;
        }
        cout << ans << endl;
    }
    return 0;
}
