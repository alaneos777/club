#include <bits/stdc++.h>
using namespace std;

vector<int> divisores;
vector<int> factores_primos;
vector<bool> repetido;

void criba1(int n){
	divisores.resize(n + 1, 0);
	for(int i = 1; i <= n; i++){
		for(int j = i; j <= n; j += i){
			divisores[j]++;
		}
	}
}

void criba2(int n){
	factores_primos.resize(n + 1, 0);
	repetido.resize(n + 1, false);
	for(int i = 2; i <= n; i++){
		if(factores_primos[i] == 0){
			for(int j = i; j <= n; j += i){
				factores_primos[j]++;
				if(j % (i * i) == 0) repetido[j] = true;
			}
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	criba1(1e6);
	criba2(1e6);
	int cnt = 1;
	for(int i = 1; i <= 1e6; i++){
		if(factores_primos[divisores[i]] == 2 && !repetido[divisores[i]]){
			if(cnt % 9 == 0) cout << i << "\n";
			cnt++;
		}
	}
	return 0;
}