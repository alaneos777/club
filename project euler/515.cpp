#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;

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

const auto primes = sieve(sqrt(1e9 + 1e5) + 10);

lli inverse(lli a, lli m){
	lli r0 = a, r1 = m, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	if(s0 < 0) s0 += m;
	return s0;
}

lli f(lli p, lli k){
	return inverse(k-1, p);
}

int main(){
	int a = 1e9, b = 1e5, k = 1e5;
	int L = a, R = a + b - 1;
	vector<bool> is(R - L + 1, true);
	for(int p : primes){
		int d = (L+p-1)/p*p;
		if(d > R) break;
		for(; d <= R; d += p){
			if(d != p){
				is[d-L] = false;
			}
		}
	}
	lli ans = 0;
	for(int p = L; p <= R; ++p){
		if(is[p-L]){
			ans += f(p, k);
		}
	}
	cout << ans << "\n";
	return 0;
}