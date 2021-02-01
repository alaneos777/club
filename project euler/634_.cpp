#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

vector<int> primes, mu;
vector<bool> is;
void sieve(int n){
	mu.resize(n+1);
	is.resize(n+1, true);
	mu[1] = 1;
	for(int i = 2; i <= n; ++i){
		if(is[i]){
			primes.push_back(i);
			mu[i] = -1;
		}
		for(int p : primes){
			int d = i*p;
			if(d > n) break;
			is[d] = false;
			if(i % p == 0) break;
			else{
				mu[d] = -mu[i];
			}
		}
	}
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

lli F(lli n){
	lli ans = 1;
	for(lli k = 1; (__int128)k*k*k <= n; ++k){
		ans += mu[k]*mu[k] * floorSqrt(n/(k*k*k));
	}
	for(lli k = 1; (__int128)k*k*k*k*k*k <= n; ++k){
		ans -= mu[k] * floorSqrt(n/(k*k*k*k*k*k));
		ans -= mu[k] * floorCbrt(n/(k*k*k*k*k*k));
	}
	ans -= upper_bound(primes.begin(), primes.end(), (lli)floorSxt(n)) - primes.begin();
	return ans;
}

const lli N = 9e18;

int main(){
	sieve(cbrtl(N) + 10);
	cout << F(N) << "\n";
	return 0;
}