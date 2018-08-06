#include <bits/stdc++.h>
using namespace std;

typedef long long int ull;

ull potencia(ull n, ull p){
	ull div = p, pot = 0;
	while(div <= n){
		pot += n / div;
		div *= p;
	}
	return pot;
}

void criba(ull n, vector<ull> & primos){
	vector<bool> es_primo(n + 1, true);
	primos.push_back(2);
	for(ull i = 3; i <= n; i += 2){
		if(es_primo[i]){
			primos.push_back(i);
			for(ull j = i * i; j <= n; j += 2 * i){
				es_primo[j] = false;
			}
		}
	}
}

void factorizar(ull n, map<ull, ull> & f, vector<ull> & primos){
	for(ull & p : primos){
		if(p * p > n) break;
		if(n % p == 0){
			ull pot = 0;
			while(n % p == 0){
				n /= p;
				++pot;
			}
			f[p] = pot;
		}
	}
	if(n > 1){
		f[n] = 1;
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	vector<ull> primos;
	criba(29, primos);
	vector<double> logaritmos(1048576 + 1, 0);
	for(ull i = 1; i <= 1048576; ++i){
		logaritmos[i] = logaritmos[i - 1] + log(i);
	}
	ull n, b;
	while(cin >> n >> b){
		map<ull, ull> f;
		factorizar(b, f, primos);
		ull ceros = -1;
		for(pair<const ull, ull> & p : f){
			if(ceros == -1){
				ceros = potencia(n, p.first) / p.second;
			}else{
				ceros = min(ceros, potencia(n, p.first) / p.second);
			}
		}
		ull digitos = floor(logaritmos[n] / log(b) + 1.0);
		cout << ceros << " " << digitos << "\n";
	}
	return 0;
}