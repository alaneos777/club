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
	criba(sqrt(5000) + 1, primos);
	int casos;
	ull m, n;
	cin >> casos;
	for(int t = 1; t <= casos; ++t){
		cin >> m >> n;
		map<ull, ull> f;
		factorizar(m, f, primos);
		ull ans = -1;
		for(pair<const ull, ull> & p : f){
			if(ans == -1){
				ans = potencia(n, p.first) / p.second;
			}else{
				ans = min(ans, potencia(n, p.first) / p.second);
			}
		}
		cout << "Case " << t << ":\n";
		if(ans == 0){
			cout << "Impossible to divide\n";
		}else{
			cout << ans << "\n";
		}
	}
	return 0;
}