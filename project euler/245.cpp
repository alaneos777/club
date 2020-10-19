#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;

auto sieve(int n){
	vector<int> primes;
	vector<bool> is(n+1, true);
	for(int i = 2; i <= n; ++i){
		if(is[i]){
			primes.push_back(i);
		}
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			is[d] = false;
			if(i % p == 0) break;
		}
	}
	return primes;
}

//447214
//288084712410001‬

int main(){
	lli ans = 0;
	int cnt = 0;
	lli M = 2e11;
	int sz = sqrt(M);
	auto primes = sieve(sz);
	vector<lli> phi(sz+1), lp(sz+1);
	int lim = (M-1)/sz;
	for(lli k = 0; k <= lim; ++k){ //l=1+sz*k // 0 <= k <= (M-1)/sz
		lli L = 1 + sz*k, R = min(L+sz-1, M);
		iota(phi.begin(), phi.end(), L);
		iota(lp.begin(), lp.end(), L);
		for(int p : primes){
			for(lli d = (L+p-1)/p*p; d <= R; d += p){
				phi[d-L] -= phi[d-L] / p;
				while(lp[d-L] % p == 0) lp[d-L] /= p;
			}
		}
		for(lli i = L; i <= R; ++i){
			if(i > 1 && lp[i-L] > 1) phi[i-L] -= phi[i-L] / lp[i-L];
			if(i > 1 && phi[i-L] != i-1 && (i-1) % (i-phi[i-L]) == 0){
				ans += i;
				cout << ++cnt << " " << i << "\n";
			}
		}
	}
	cout << ans << "\n";
	return 0;
}