#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli N = 9e18;

auto sieve(uint32_t n){
	vector<bool> is(n+1, true);
	vector<uint32_t> primes;
	for(uint32_t i = 2; i <= n; ++i){
		if(is[i]) primes.push_back(i);
		for(uint32_t p : primes){
			if((lli)i * p > n) break;
			uint32_t d = i * p;
			is[d] = false;
			if(i % p == 0) break;
		}
	}
	return primes;
}

const auto primes = sieve((uint32_t)sqrtl(N));

// Powerful numbers <= n
lli f(lli n, int idx = 0){
	lli ans = 1;
	for(int i = idx; i < primes.size(); ++i){
		lli p = primes[i];
		lli curr = n / (p * p);
		if(!curr) break;
		while(curr >= 1){
			ans += f(curr, i+1);
			curr /= p;
		}
	}
	return ans;
}

// Squarefree numbers <= n
lli g(lli n, int idx = 0){
	lli ans = n;
	for(int i = idx; i < primes.size(); ++i){
		lli p = primes[i];
		lli curr = n / (p * p);
		if(!curr) break;
		ans -= g(curr, i+1);
	}
	return ans;
}

// Cubefree numbers <= n
lli h(lli n, int idx = 0){
	lli ans = n;
	for(int i = idx; i < primes.size(); ++i){
		lli p = primes[i];
		lli curr = n / (p * p) / p;
		if(!curr) break;
		ans -= h(curr, i+1);
	}
	return ans;
}

lli floorSqrt(lli n){
	lli r = sqrtl(n);
	for(lli x = max(0ll, r-2); x <= r+2; ++x){
		if((__int128)x*x > n) return x-1;
	}
	return r;
}

lli floorCbrt(lli n){
	lli r = cbrtl(n);
	for(lli x = max(0ll, r-2); x <= r+2; ++x){
		if((__int128)x*x*x > n) return x-1;
	}
	return r;
}

lli floorSxt(lli n){
	lli r = powl(n, 1.0l/6.0l);
	for(lli x = max(0ll, r-2); x <= r+2; ++x){
		if((__int128)x*x*x*x*x*x > n) return x-1;
	}
	return r;
}

int main(){
	lli ans = f(N)-1;
	ans -= (lli)g(floorCbrt(N))-1;
	ans -= (lli)h(floorSqrt(N))-1;
	int less = upper_bound(primes.begin(), primes.end(), (lli)floorSxt(N)) - primes.begin();
	ans -= less;
	cout << ans << "\n";
	return 0;
}