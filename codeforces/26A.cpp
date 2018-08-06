#include <bits/stdc++.h>

using namespace std;

vector< vector<int> > factores_primos;
vector<bool> es_primo;

void criba_primos(int n){
    es_primo.resize(n+1, true);
    es_primo[0] = es_primo[1] = false;
    int bound = sqrt(n);
    for(int i=2;i<=bound;i++){
        while(!es_primo[i]) i++;
        for(int j=2*i;j<=n;j+=i){
            es_primo[j] = false;
        }
    }
}

void criba_factores_primos(int n){
    factores_primos.resize(n+1, vector<int>());
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j+=i){
            if(es_primo[i]){
                factores_primos[j].push_back(i);
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    int n, ans = 0;
    cin >> n;
    criba_primos(n);
    criba_factores_primos(n);
    for(int i=1;i<=n;i++){
        if(factores_primos[i].size()==2) ans++;
    }
    cout << ans;
    return 0;
}
