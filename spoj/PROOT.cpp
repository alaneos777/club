#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

vector<lli> primos;

void criba(lli n){
	vector<bool> es_primo(n + 1, true);
	primos.push_back(2);
	lli limit = sqrt(n);
	for(lli i = 3; i <= n; i += 2){
		if(es_primo[i]){
			primos.push_back(i);
			if(i <= limit){
				for(lli j = i * i; j <= n; j += 2 * i){
					es_primo[j] = false;
				}
			}
		}
	}
}

void factorizar(lli n, map<lli, lli> & f){
	for(lli & p : primos){
		if(p * p > n) break;
		if(n % p == 0){
			lli pot = 0;
			while(n % p == 0){
				n /= p;
				++pot;
			}
			f[p] = pot;
		}
	}
	if(n > 1) f[n] = 1;
}

lli exp_bin(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = (ans * a);
		b >>= 1;
		a = (a * a);
	}
	return ans;
}

lli exp_bin_mod(lli a, lli b, lli n){
	lli ans = 1;
	while(b){
		if(b & 1) ans = (ans * a) % n;
		b >>= 1;
		a = (a * a) % n;
	}
	return ans;
}

lli multiplicativeOrder(lli a, lli mod, map<lli, lli> & f){
	lli n = mod - 1, a1;
	lli order = n;
	for(pair<const lli, lli> & factor : f){
		lli p = factor.first, e = factor.second;
		order /= exp_bin(p, e);
		a1 = exp_bin_mod(a, order, mod);
		while(a1 != 1){
			a1 = exp_bin_mod(a1, p, mod);
			order *= p;
		}
	}
	return order;
}

int main(){
	ios_base::sync_with_stdio(0);
	criba(46341);
	lli p, r;
	int n;
	while(cin >> p >> n && !(p == 0 && n == 0)){
		map<lli, lli> f;
		factorizar(p - 1, f);
		while(n--){
			cin >> r;
			if(r != 0 && multiplicativeOrder(r, p, f) == (p - 1)){
				cout << "YES\n";
			}else{
				cout << "NO\n";
			}
		}
	}
	return 0;
}