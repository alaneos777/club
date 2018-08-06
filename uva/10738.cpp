#include <bits/stdc++.h>

using namespace std;

map<int, int> factorizar(int n){
    map<int, int> f;
    if(n==1) return f;
    int d=2;
    while(d<=sqrt(n)){
        if(n%d==0){
            f[d]++;
            n /= d;
        }else{
            d++;
        }
    }
    f[n]++;
    return f;
}

int mu(int n){
    map<int, int> f = factorizar(n);
    int p_f = 0;
    for(pair<int, int> p:f){
        if(p.second>1){
            return 0;
        }
        p_f++;
    }
    if(p_f%2==0) return 1;
    else return -1;
}

vector<int> valores_mu;

int M(int n){
    int ans = 0;
    for(int i=1;i<=n;i++) ans += valores_mu[i];
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    int n, maximo = 0;
    vector<int> casos;
    while(cin >> n){
        if(n==0) break;
        if(n > maximo) maximo = n;
        casos.push_back(n);
    }
    valores_mu.push_back(0);
    for(int i=1;i<=maximo;i++){
        valores_mu.push_back(mu(i));
    }
    for(int caso:casos){
        cout << setw(8) << caso << setw(8) << valores_mu[caso] << setw(8) << M(caso) << endl;
    }
    return 0;
}
