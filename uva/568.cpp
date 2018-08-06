#include <bits/stdc++.h>
using namespace std;

void criba_primos(int n, vector<int> & primos){
	vector<bool> es_primo(n + 1, true);
	es_primo[0] = es_primo[1] = false;
	for(int i = 4; i <= n; i += 2)
		es_primo[i] = false;
	int limit = sqrt(n);
	for(int i = 3; i <= limit; i += 2)
		if(es_primo[i])
			for(int j = i * i; j <= n; j += 2 * i)
				es_primo[j] = false;
	primos.push_back(2);
	for(int i = 3; i <= n; i += 2)
		if(es_primo[i])
			primos.push_back(i);
}

int potencia(int n, int p){
	int ans = 0, pot = p, tmp;
	while(true){
		tmp = n / pot;
		if(tmp == 0) break;
		ans += tmp;
		pot *= p;
	}
	return ans;
}

int factorizar_factorial(int n, vector<int> & primos, vector<int> & f){
	int i = 0, p;
	for(i = 0; i < primos.size(); ++i){
		p = primos[i];
		if(p > n) break;
		f[i] = potencia(n, p);
	}
	return i - 1;
}

int exp_bin_mod(int a, int b, int m){
	int ans = 1;
	while(b){
		if(b & 1) ans = (ans * a) % m;
		b >>= 1;
		a  = (a * a) % m;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	int maximo = 1e4, n;
	vector<int> primos;
	criba_primos(maximo, primos);
	while(cin >> n){
		vector<int> f(primos.size(), 0);
		int limit = factorizar_factorial(n, primos, f);
		int diez = min(f[0], f[2]);
		f[0] -= diez;
		f[2] -= diez;
		int ans = 1;
		for(int i = 0; i <= limit; ++i){
			if(f[i] > 0) ans = (ans * exp_bin_mod(primos[i], f[i], 10)) % 10;
		}
		cout << setw(5) << n;
		cout << " -> " << ans << "\n";
	}
	return 0;
}