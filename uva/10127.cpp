#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

vector<int> primos;

lli exp_bin_mod(lli a, int b, int n){
	lli ans = 1;
	while(b){
		if(b & 1) ans = (ans * a) % n;
		b >>= 1;
		a = (a * a) % n;
	}
	return ans;
}

void criba(int n){
	primos.push_back(2);
	vector<bool> es_primo(n + 1, true);
	int limit = sqrt(n);
	for(int i = 3; i <= n; i++){
		if(es_primo[i]){
			primos.push_back(i);
			if(i <= limit){
				for(int j = i * i; j <= n; j += 2 * i){
					es_primo[j] = false;
				}
			}
		}
	}
}

int phi(int n){
	int ans = n;
	for(int p : primos){
		if(p * p > n) break;
		if(n % p == 0){
			while(n % p == 0) n /= p;
			ans -= ans / p;
		}
	}
	if(n > 1) ans -= ans / n;
	return ans;
}

int multiplicativeOrder(int a, int mod){
	int n = phi(mod);
	lli a1;
	int order = n;
	for(int p : primos){
		if(p * p > n) break;
		if(n % p == 0){
			while(n % p == 0){
				n /= p, order /= p;
			}
			a1 = exp_bin_mod(a, order, mod);
			while(a1 != 1){
				a1 = exp_bin_mod(a1, p, mod);
				order *= p;
			}
		}
	}
	if(n > 1){
		order /= n;
		a1 = exp_bin_mod(a, order, mod);
		while(a1 != 1){
			a1 = exp_bin_mod(a1, n, mod);
			order *= n;
		}
	}
	return order;
}

int main(){
	ios_base::sync_with_stdio(0);
	criba(301);
	int n;
	while(cin >> n){
		cout << multiplicativeOrder(10, 9 * n) << "\n";
	}
	return 0;
}