#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

vector<int> sieve(int n){
	vector<int> primes;
	vector<bool> isPrime(n+1, true);
	for(int i = 2; i <= n; ++i){
		if(isPrime[i])
			primes.push_back(i);
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			isPrime[d] = false;
			if(i % p == 0) break;
		}
	}
	return primes;
}

const int N = 20000;
vector<int> primes = sieve(N);

vector<vector<pair<int, int>>> fact(int n){
	vector<vector<pair<int, int>>> f(n+1);
	vector<int> cnt(n+1), acum(n+1), primes;
	vector<bool> isPrime(n+1, true);
	for(int i = 2; i <= n; ++i){
		if(isPrime[i]){ //case base: f(p)
			primes.push_back(i);
			f[i].emplace_back(i, 1);
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

lli mod = 1e9 + 7;

lli inverse(lli a, lli n){
	lli r0 = a, r1 = n, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	if(s0 < 0) s0 += n;
	return s0;
}

lli powerMod(lli a, lli b, lli m){
	a %= m;
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans;
}

int main(){
	vector<map<int, int>> facts_fact(N+1), B(N+1);
	auto facts = fact(N);
	for(int i = 2; i <= N; ++i){
		facts_fact[i] = facts_fact[i-1];
		for(auto f : facts[i]){
			facts_fact[i][f.first] += f.second;
		}
	}
	for(int i = 2; i <= N; ++i){
		B[i] = B[i-1];
		for(auto f : facts[i]){
			B[i][f.first] += i * f.second;
		}
		for(auto f : facts_fact[i]){
			B[i][f.first] -= f.second;
		}
	}
	lli ans = 0;
	for(int i = 1; i <= N; ++i){
		lli d = 1;
		for(auto f : B[i]){
			if(f.second){
				d = d * (powerMod(f.first, f.second + 1, mod) - 1) % mod * inverse(f.first - 1, mod) % mod;
			}
		}
		if(d < 0) d += mod;
		ans = (ans + d) % mod;
	}
	cout << ans << "\n";
	return 0;
}