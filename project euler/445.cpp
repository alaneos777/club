#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli mod = 1e9 + 7;
const int N = 1e7;

auto sieve(int n){
	vector<vector<pair<int, int>>> f(n+1);
	vector<int> cnt(n+1), acum(n+1), primes;
	vector<bool> isPrime(n+1, true);
	for(int i = 2; i <= n; ++i){
		if(isPrime[i]){ //case base: f(p)
			f[i].emplace_back(i, 1);
			primes.push_back(i);
			cnt[i] = 1;
			acum[i] = i;
		}
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			isPrime[d] = false;
			if(i % p == 0){ //gcd(i, p) != 1
				f[d] = f[i / acum[i]];
				f[d].emplace_back(p, cnt[i] + 1);
				cnt[d] = cnt[i] + 1;
				acum[d] = acum[i] * p;
				break;
			}else{ //gcd(i, p) = 1
				f[d] = f[i];
				f[d].emplace_back(p, 1);
				cnt[d] = 1;
				acum[d] = p;
			}
		}
	}
	return f;
}

const auto facts = sieve(N);

lli powerMod(lli a, lli b){
	a %= mod;
	b %= mod-1;
	if(b < 0) b += mod-1;
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

int main(){
	vector<lli> fact(N+1);
	lli sum = 0;
	lli acum = 1;
	lli ncr = 1;
	for(int k = 0; k < N; ++k){
		sum += acum - ncr;
		if(sum >= mod) sum -= mod;
		if(sum < 0) sum += mod;
		ncr = ncr * (N - k) % mod * powerMod(k + 1, -1) % mod;
		for(const auto & par : facts[N-k]){
			int p, a;
			tie(p, a) = par;
			if(fact[p]) acum = acum * powerMod(1 + powerMod(p, fact[p]), -1) % mod;
			fact[p] += a;
			if(fact[p]) acum = acum * (1 + powerMod(p, fact[p])) % mod;
		}
		for(const auto & par : facts[k+1]){
			int p, a;
			tie(p, a) = par;
			if(fact[p]) acum = acum * powerMod(1 + powerMod(p, fact[p]), -1) % mod;
			fact[p] -= a;
			if(fact[p]) acum = acum * (1 + powerMod(p, fact[p])) % mod;
		}
	}
	cout << sum << "\n";
	return 0;
}