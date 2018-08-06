#include <bits/stdc++.h>
using namespace std;

void criba(int n, vector<int> & primos){
	vector<bool> marcas(n + 1, true);
	primos.push_back(2);
	for(int i = 3; i <= n; i += 2){
		if(marcas[i]){
			primos.push_back(i);
			for(int j = i * i; j <= n; j += 2 * i){
				marcas[j] = false;
			}
		}
	}
}

void factorizar(int n, map<int, int> & f, vector<int> & primos){
	for(int i = 0; i < primos.size(); ++i){
		int p = primos[i];
		if(p * p > n) break;
		if(n % p == 0){
			int pot = 0;
			while(n % p == 0){
				n /= p;
				++pot;
			}
			if(f[p] == pot){
				f[p] = 0;
			}else{
				f[p] = max(pot, f[p]);
			}
		}
	}
	if(n > 1){
		if(f[n] == 1){
			f[n] = 0;
		}else{
			f[n] = max(1, f[n]);
		}
	}
}

int exp_bin(int a, int b){
	int ans = 1;
	while(b){
		if(b & 1) ans *= a;
		b >>= 1;
		a *= a;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	int t;
	int a, c;
	vector<int> primos;
	criba(sqrt(1e7), primos);
	cin >> t;
	for(int i = 1; i <= t; ++i){
		cin >> a >> c;
		if(c % a == 0){
			int ans = 1;
			map<int, int> f;
			factorizar(c, f, primos);
			factorizar(a, f, primos);
			for(pair<const int, int> & par : f){
				ans *= exp_bin(par.first, par.second);
			}
			cout << ans << "\n";
		}else{
			cout << "NO SOLUTION\n";
		}
	}
	return 0;
}