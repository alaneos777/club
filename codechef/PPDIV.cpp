#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9 + 7;

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a;
		b >>= 1;
		a = a * a;
	}
	return ans;
}

auto mu_sieve(int n){
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
			if(i % p == 0) break;
			else mu[d] = -mu[i];
		}
	}
	return mu;
}

const int M = 59;
const auto mu = mu_sieve(M);

const lli inv_6 = 166666668;
lli sq(lli n){
	n %= mod;
	return n * (n+1) % mod * (2*n+1) % mod * inv_6 % mod;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		lli n;
		cin >> n;
		lli ans = n % mod;
		for(int p = 3; p <= M; ++p){
			if(mu[p] == 0) continue;
			lli term = 0;
			lli lim = powl(n, 1.0l/p);
			if(lim == 1) break;
			for(lli k = 2; k <= lim; ++k){
				lli kp = power(k, p);
				term += (kp % mod) * ((n / kp) % mod) % mod;
				if(term >= mod) term -= mod;
			}
			if(mu[p] == 1){
				ans -= term;
				if(ans < 0) ans += mod;
			}else if(mu[p] == -1){
				ans += term;
				if(ans >= mod) ans -= mod;
			}
		}
		lli k = 2;
		while(k*k <= n){
			lli d = n / (k*k), u = sqrtl(n/d);
			ans += (d % mod) * (sq(u) - sq(k-1)) % mod;
			if(ans < 0) ans += mod;
			if(ans >= mod) ans -= mod;
			k = u+1;
		}
		cout << ans << "\n";
	}
	return 0;
}