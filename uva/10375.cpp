#include <bits/stdc++.h>
using namespace std;
typedef long double ld;

vector<int> primos;

void criba(int n){
	vector<bool> es_primo(n + 1, true);
	primos.push_back(2);
	int limit = sqrt(n);
	for(int i = 3; i <= n; i += 2){
		if(es_primo[i]){
			primos.push_back(i);
			if(i <= limit){
				for(int j = i * i; j <= n; j += 2*i){
					es_primo[j] = false;
				}
			}
		}
	}
}

int potencia(int n, int p){
	int ans = 0;
	int pot = p;
	while(pot <= n){
		ans += n / pot;
		pot *= p;
	}
	return ans;
}

void factorizar_factorial(int n, int m, map<int, int> & f){
	for(int p : primos){
		if(p > n) break;
		f[p] += potencia(n, p) * m;
	}
}

ld exp_bin(ld a, int b){
	ld ans = 1;
	while(b){
		if(b & 1) ans *= a;
		b >>= 1;
		a *= a;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	criba(10000);
	int p, q, r, s;
	while(cin >> p >> q >> r >> s){
		map<int, int> f;
		factorizar_factorial(p, 1, f);
		factorizar_factorial(q, -1, f);
		factorizar_factorial(p - q, -1, f);
		factorizar_factorial(r, -1, f);
		factorizar_factorial(s, 1, f);
		factorizar_factorial(r - s, 1, f);
		ld ans = 1;
		for(pair<int, int> factor : f){
			ld pot = exp_bin(factor.first, abs(factor.second));
			if(factor.second > 0){
				ans *= pot;
			}else if(factor.second < 0){
				ans /= pot;
			}
		}
		cout << fixed << setprecision(5) << ans << "\n";
	}
	return 0;
}