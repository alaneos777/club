#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli mod = 1e9 + 7;

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

const int M = 60;
vector<lli> fact(M+1, 1), inv(M+1, 1), invfact(M+1, 1), bernoulli(M+1, 1);

lli ncr(lli n, lli r){
	return fact[n] * invfact[r] % mod * invfact[n - r] % mod;
}

lli G(lli n, int m){
	n %= mod;
	lli ans = 0;
	for(int k = 0; k <= m; ++k){
		ans += ncr(m + 1, k) * bernoulli[k] % mod * power(n, m + 1 - k) % mod;
		if(ans >= mod) ans -= mod;
	}
	ans = ans * inv[m + 1] % mod;
	return ans;
}

const lli N = 1e12;
const int K = 50;

auto sieve(int n){
	vector<bool> is(n+1, true);
	vector<int> primes;
	for(int i = 2; i <= n; ++i){
		if(is[i]) primes.push_back(i);
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			is[d] = false;
			if(i % p == 0) break;
		}
	}
	return primes;
}

const auto primes = sieve(sqrt(N) + 100);

lli f(lli n, int m, int idx = 0){
	lli ans = G(n, m);
	for(int i = idx; i < primes.size(); ++i){
		lli p = primes[i];
		lli curr = n / (p * p);
		if(!curr) break;
		lli pw = power(p, m);
		lli acum = (-pw) % mod * (pw - 1) % mod;
		if(acum < 0) acum += mod;
		int e = 1;
		while(curr >= 1){
			ans += acum * f(curr, m, i+1) % mod;
			if(ans >= mod) ans -= mod;
			curr /= p;
			++e;
		}
	}
	return ans;
}

int main(){
	for(int i = 2; i <= M; ++i){
		fact[i] = fact[i-1] * i % mod;
		inv[i] = mod - (mod / i) * inv[mod % i] % mod;
		invfact[i] = invfact[i-1] * inv[i] % mod;
	}
	for(int n = 1; n <= M; ++n){
		for(int k = 0; k < n; ++k){
			bernoulli[n] -= bernoulli[k] * ncr(n, k) % mod * inv[n - k + 1] % mod;
			if(bernoulli[n] < 0) bernoulli[n] += mod;
		}
	}
	lli ans = 0;
	for(int k = 1; k <= K; ++k){
		ans += f(N, k);
		if(ans >= mod) ans -= mod;
		cout << k << "\n";
	}
	cout << ans << "\n";
	return 0;
}