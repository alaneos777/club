#include <bits/stdc++.h>

using namespace std;

vector<bool> es_primo;
vector< vector<int> > factores_primos;

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
        if(es_primo[i]){
            for(int j=i;j<=n;j+=i){
                factores_primos[j].push_back(i);
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int a, b;
    cin >> a >> b;
    criba_primos(b);
    criba_factores_primos(b);
    int ans = 0;
    for(int i=a;i<=b;i++){
        int n_f = 0, n=i*1;
        for(int fi:factores_primos[i]){
            while(n%fi==0){
                n /= fi;
                n_f++;
            }
        }
        if(es_primo[n_f]) ans++;
    }
    cout << ans;
    return 0;
}
