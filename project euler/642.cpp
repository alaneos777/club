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

const lli M = 201820182018ll;
const int sz = sqrt(M);
const int mod = 1e9;

const auto primes = sieve(sz);

/*
[0 149748]      121927106
[149749 299496] 172565753
[299497 449244] 337006185
*/

int main(){
	lli ans = 0;
	int lim = (M - 1) / sz;
	vector<lli> lp(sz+1), rem(sz+1);
	for(lli k = 0; k <= lim; ++k){
		lli L = 1 + sz*k, R = min(L+sz-1, M);
		cout << L << " " << R << "\n";
		iota(lp.begin(), lp.end(), L);
		iota(rem.begin(), rem.end(), L);
		for(int p : primes){
			for(lli d = (L+p-1)/p*p; d <= R; d += p){
				lp[d-L] = p;
				while(rem[d-L] % p == 0) rem[d-L] /= p;
			}
		}
		for(lli i = max(2ll, L); i <= R; ++i){
			if(rem[i-L] > 1) lp[i-L] = rem[i-L];
			ans = (ans + lp[i-L]) % mod;
		}
	}
	cout << ans << "\n";
	return 0;
}