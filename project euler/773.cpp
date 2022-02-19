#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9 + 7;

auto sieve(int n){
	vector<int> primes;
	vector<bool> is(n+1, true);
	for(int i = 2; i <= n; ++i){
		if(is[i]) primes.push_back(i);
		for(int p : primes){
			int d = i*p;
			if(d > n) break;
			is[d] = false;
			if(i % p == 0) break;
		}
	}
	return primes;
}

const auto primes = sieve(1e5);

int F(int n){
	lli Q = 1, phi = 1, x = 2, y = 6;
	int cnt = 0;
	for(int p : primes){
		if(p % 10 != 7) continue;
		cnt++;
		Q = Q * p % mod;
		phi = phi * (p-1) % mod;
		tie(x, y) = make_pair(y, 2*(y-x) % mod);
		if(y < 0) y += mod;
		if(cnt == n) break;
	}
	assert(cnt == n);
	return Q * (5*phi + x) % mod;
}

int main(){
	cout << F(97) << "\n";
	return 0;
}