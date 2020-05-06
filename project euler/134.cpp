#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

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

const int M = 1e6;
const auto primes = sieve(M + 1000);

lli inv(lli a, lli m){
	lli r0 = a, r1 = m, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	if(s0 < 0) s0 += m;
	return s0;
}

int main(){
	vector<int> ten = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000};
	lli sum = 0;
	for(int i = 2; i < primes.size(); ++i){
		int p1 = primes[i];
		int p2 = primes[i+1];
		if(p1 > M) break;
		int m1 = ten[to_string(p1).size()];
		// n = p1 mod 10^len(p1)
		// n = 0  mod p2
		// n = p1*p2*inv(p2, m1) mod (m1*p2)
		lli mod = lli(m1) * p2;
		lli n = lli(p1) * p2 % mod * inv(p2, m1) % mod;
		sum += n;
	}
	cout << sum << "\n";
	return 0;
}