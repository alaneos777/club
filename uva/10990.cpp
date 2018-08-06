#include <bits/stdc++.h>

using namespace std;

vector<bool> es_primo;

void criba(int n){
    es_primo.resize(n+1, true);
    es_primo[1] = false;
    int bound = sqrt(n);
    for(int i=2;i<=bound;i++){
        while(!es_primo[i]) i++;
        for(int j=2*i;j<=n;j+=i){
            es_primo[j] = false;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    int N, m, n, maximo = 0;
    cin >> N;
    vector< pair<int, int> > casos(N);
    for(int i=0;i<N;i++){
        cin >> m >> n;
        if(n>maximo) maximo = n;
        casos[i] = make_pair(m, n);
    }
    vector<int> valores_phi(maximo+1), valores_depthphi(maximo+1, 0), barrido(maximo+1, 0);
    for(int i=1;i<=maximo;i++){
        valores_phi[i] = i;
    }
    criba(maximo);
    for(int i=1;i<=maximo;i++){
        if(es_primo[i]){
            for(int j=i;j<=maximo;j+=i){
                valores_phi[j] -= valores_phi[j]/i;
            }
        }
    }
    for(int i=2;i<=maximo;i++){
        valores_depthphi[i] = 1 + valores_depthphi[valores_phi[i]];
        barrido[i] = barrido[i-1] + valores_depthphi[i];
    }
    for(pair<int, int> caso:casos){
        cout << barrido[caso.second]-barrido[caso.first-1] << endl;
    }
    return 0;
}
