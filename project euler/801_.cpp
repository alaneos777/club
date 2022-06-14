#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 993353399;

auto sieve(int n){
	vector<int> primes;
	vector<bool> is(n+1, true);
	for(int i = 2; i <= n; ++i){
		if(is[i]) primes.push_back(i);
		for(int p : primes){
			int d = i*p;
			if(d > n) break;
			is[d] = false;
			if(i%p == 0) break;
		}
	}
	return primes;
}

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b&1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

lli calc_f(lli p, int a){
	p %= mod;
	lli ans = power(p, 2*a-1) * (power(p, a) * (p+1) % mod - 1) % mod;
	if(ans < 0) ans += mod;
	return ans;
}

int main(){
	lli L = 1e16, R = L+1e6;
	auto primes = sieve(sqrtl(R));
	vector<lli> rem(R - (L-1) + 1);
	iota(rem.begin(), rem.end(), L-1);
	vector<lli> f(R - (L-1) + 1, 1);
	vector<bool> is(R - (L-1) + 1, true);
	for(int p : primes){
		for(lli k = ((L-1)+p-1)/p; k <= R/p; ++k){
			int idx = k*p - (L-1);
			int a = 0;
			while(rem[idx]%p == 0){
				rem[idx] /= p;
				a++;
			}
			(f[idx] *= calc_f(p, a)) %= mod;
			if(k > 1) is[idx] = false;
		}
	}
	for(lli i = L-1; i <= R; ++i){
		int idx = i - (L-1);
		if(rem[idx] > 1){
			(f[idx] *= calc_f(rem[idx], 1)) %= mod;
			rem[idx] = 1;
		}
	}
	lli ans = 0;
	for(lli p = L; p <= R; ++p){
		int idx = p - (L-1);
		if(is[idx]) ans += (f[idx-1] + ((p-1)%mod) * ((p-1)%mod)) % mod;
		if(ans >= mod) ans -= mod;
	}
	cout << ans << "\n";
	return 0;
}