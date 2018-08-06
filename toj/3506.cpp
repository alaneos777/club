#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

void criba(lli n, vector<lli> & primos){
	vector<bool> es_primo(n + 1, true);
	primos.push_back(2);
	lli limit = sqrt(n);
	for(lli i = 3; i <= n; i += 2){
		if(es_primo[i]){
			primos.push_back(i);
			if(i <= limit)
			for(lli j = i * i; j <= n; j += 2 * i){
				es_primo[j] = false;
			}
		}
	}
}

lli phi(lli n, vector<lli> & primos){
	lli ans = n;
	for(int i = 0; i < primos.size(); i++){
		lli p = primos[i];
		if(p * p > n) break;
		if(n % p == 0){
			while(n % p == 0) n /= p;
			ans -= ans / p;
		}
	}
	if(n > 1) ans -= ans / n;
	return ans;
}

lli exp_bin_mod(lli a, lli b, lli m){
	lli ans = 1;
	while(b){
		if(b & 1) ans = (ans * a) % m;
		b >>= 1;
		a = (a * a) % m;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	vector<lli> primos;
	criba(3163, primos);
	lli n, m, mod = 201004;
	while(cin >> n >> m && !(n == 0 && m == 0)){
		lli ans = (exp_bin_mod(n, m - 1, mod) * phi(n, primos)) % mod;
		cout << ans << "\n";
	}
	return 0;
}