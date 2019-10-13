#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli mod = 1e9 + 87;
const int limit = 1e7;

vector<vector<pair<int, int>>> sieve(int n){
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

const vector<vector<pair<int, int>>> facts = sieve(limit);

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
	lli sum = 0;
	map<int, lli> fact;
	lli acum = 1;
	for(lli i = 2; i <= limit; ++i){
		for(auto & par : facts[i]){
			int p, a;
			tie(p, a) = par;
			acum = acum * powerMod(2*fact[p] + 1, -1) % mod;
			fact[p] += a;
			acum = acum * (2*fact[p] + 1) % mod;
		}
		sum += acum;
		if(sum >= mod) sum -= mod;
	}
	cout << sum << "\n";
	return 0;
}