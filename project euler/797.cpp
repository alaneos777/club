#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9 + 7;

lli power(lli a, lli b){
	if(b < 0) b += mod-1;
	lli ans = 1;
	while(b){
		if(b&1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

auto muSieve(int n){
	vector<int> primes, mu(n+1);
	vector<bool> is(n+1, true);
	mu[1] = 1;
	for(int i = 2; i <= n; ++i){
		if(is[i]){
			mu[i] = -1;
			primes.push_back(i);
		}
		for(int p : primes){
			int d = i*p;
			if(d > n) break;
			is[d] = false;
			if(i%p == 0) break;
			else mu[d] = -mu[i];
		}
	}
	return mu;
}


const int M = 1e7;
auto U = muSieve(M);

int main(){
	vector<int> cyc_2(M+1);
	for(int i = 1; i <= M; ++i){
		cyc_2[i] = (2*cyc_2[i-1] + 1) % mod;
	}

	for(int d = 1; d <= M; ++d){
		lli den = power(cyc_2[d], -1);
		for(int i = 2*d; i <= M; i += d){
			cyc_2[i] = cyc_2[i] * den % mod;
		}
	}

	partial_sum(U.begin(), U.end(), U.begin());

	vector<int> terms(M+1, 1);
	for(int d = 1; d <= M; ++d){
		for(int k = d; k <= M; k += d){
			terms[k] = (lli)terms[k] * (cyc_2[d] + 1) % mod;
		}
	}

	lli ans = 0;
	for(int k = 1; k <= M; ++k){
		ans += (lli)terms[k] * U[M/k] % mod;
		if(ans >= mod) ans -= mod;
		if(ans < 0) ans += mod;
	}

	cout << ans << "\n";
	return 0;
}