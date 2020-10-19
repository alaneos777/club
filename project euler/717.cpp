#include <bits/stdc++.h>
using namespace std;
using lli = __int128_t;

lli power(lli a, lli b, lli m){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans;
}

int g(lli p){
	lli y = power(2, power(2, p, p-1), p);
	lli inv2 = (p + 1) / 2;
	lli z0 = (y * inv2 % p) * power(2, p, p*p) % (p*p);
	return z0 / p;
}

auto sieve(int n){
	vector<int> primes;
	vector<bool> is(n+1, true);
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

int main(){
	int N = 1e7;
	auto primes = sieve(N-1);
	int64_t ans = 0;
	for(int p : primes){
		if(p != 2) ans += g(p);
	}
	cout << ans << "\n";
	return 0;
}