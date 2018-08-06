#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;

vector<bool> es_primo;
vector<ull> primos;

void criba(ull n){
    es_primo.resize(n+1, true);
    es_primo[1] = false;
    ull bound = sqrt(n);
    for(ull i=2;i<=bound;i++){
        while(!es_primo[i]) i++;
        for(ull j=2*i;j<=n;j+=i){
            es_primo[j] = false;
        }
    }
    for(ull i=1;i<=n;i++) if(es_primo[i]) primos.push_back(i);
}

int main()
{
    ull n, maximo = 200000;
    vector<ull> phi(maximo+1), barrido(maximo+1, 0);
    for(ull i=1;i<=maximo;i++){
        phi[i] = i;
    }
    criba(maximo);
    for(ull i=1;i<=maximo;i++){
        if(es_primo[i]){
            for(ull j=i;j<=maximo;j+=i){
                phi[j] -= phi[j]/i;
            }
        }
    }
    phi[1]++;
    for(ull i=1;i<=maximo;i++){
        barrido[i] = barrido[i-1] + phi[i];
    }
    while(cin >> n){
        if(n==0) break;
        if(n==1){
            cout << "0/1\n";
            continue;
        }
        if(n==2){
            cout << "1/1\n";
            continue;
        }
        for(ull i=1;i<=maximo;i++){
            if(n <= barrido[i]){
                ull pos = n-barrido[i-1];
                ull contador = 0;
                ull den = i*1;
                ull c;
                vector<ull> f;
                for(ull primo:primos){
                    if(primo>i) break;
                    ull tmp = 0;
                    while(i%primo==0){
                        tmp++;
                        i /= primo;
                    }
                    if(tmp>0) f.push_back(primo);
                }
                for(ull j=1;j<=den;j++){
                    bool test = true;
                    for(ull ff:f){
                        if(j%ff==0){
                            test = false;
                            break;
                        }
                    }
                    if(test){
                        contador++;
                        if(contador==pos){
                            c = j*1;
                            break;
                        }
                    }
                }
                cout << c << "/" << den << "\n";
                break;
            }
        }
    }
    return 0;
}
