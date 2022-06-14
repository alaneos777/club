#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1020340567;

auto muSieve(int n){
	vector<int> primes, mu(n+1);
	vector<bool> is(n+1, true);
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
			if(i%p == 0) break;
			else mu[d] = -mu[i];
		}
	}
	partial_sum(mu.begin(), mu.end(), mu.begin());
	return mu;
}

const int M = 1e7;
const auto U = muSieve(M);

int main(){
	lli ans = 0;
	lli pw = 1;
	for(int i = 1; i <= M; ++i){
		ans += (i==1 ? 2 : pw) * U[M/i] % mod;
		if(ans >= mod) ans -= mod;
		if(ans < 0) ans += mod;
		pw = pw*2 % mod;
	}
	cout << ans << "\n";
	return 0;
}