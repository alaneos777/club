#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli mod = 1e9 + 7;

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b&1) ans *= a;
		b >>= 1;
		a *= a;
	}
	return ans;
}

const int M = 100;
vector<lli> fact(M+1, 1), inv(M+1, 1), invfact(M+1, 1);
map<lli, int> mem[M+1];

lli ncr(int n, int r){
	if(r < 0 || r > n) return 0;
	return fact[n] * invfact[r] % mod * invfact[n-r] % mod;
}

// https://oeis.org/A000123
int g(lli n, int t, int k){
	if(n < 0) return 0;
	if(n == 0 || t == 0) return 1;
	if(mem[t].count(n)) return mem[t][n];
	lli ans = 0;
	lli pw = power(k, t-1);
	if(n < t*pw){
		ans = g(n - pw, t, k) + g(n, t-1, k);
		if(ans >= mod) ans -= mod;
	}else{
		for(int i = 1; i <= t+1; ++i){
			lli r = g(n - i*pw, t, k) * ncr(t+1, i) % mod;
			if(i&1){
				ans += r;
				if(ans >= mod) ans -= mod;
			}else{
				ans -= r;
				if(ans < 0) ans += mod;
			}
		}
	}
	return mem[t][n] = ans;
}

int f(lli n, int k){
	for(int i = 0; i <= M; ++i){
		mem[i].clear();
	}
	int t = logl(n)/logl(k) + 1;
	return g(n, t, k);
}

int main(){
	for(lli i = 2; i <= M; ++i){
		fact[i] = i * fact[i-1] % mod;
		inv[i] = mod - (mod / i) * inv[mod % i] % mod;
		invfact[i] = inv[i] * invfact[i-1] % mod;
	}
	lli N = 1e14;
	lli ans = 0;
	for(int k = 2; k <= 10; ++k){
		ans += f(N, k);
		if(ans >= mod) ans -= mod;
	}
	cout << ans << "\n";
	return 0;
}