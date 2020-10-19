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

lli power(lli a, lli b, lli m){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans;
}

const int M = 50000;
const int mod = 1953125; //5^9
const int modulo = 1e9; //10^9
const int phi_mod = 1562500; //4*5^8
const auto primes = sieve(M);

int main(){
	int sz = logl(M) / logl(2);
	vector<int> freq(sz + 1), acum(sz + 1), sol(sz + 1);
	for(int p : primes){
		int pot = logl(M) / logl(p);
		freq[pot]++;
	}
	for(int i = 1; i <= sz; ++i){
		acum[i] = acum[i-1] + freq[i];
	}
	int mx = freq[1];
	vector<vector<int>> ncr(mx+1, vector<int>(mx+1));
	ncr[0][0] = 1;
	for(int i = 1; i <= mx; ++i){
		ncr[i][0] = ncr[i][i] = 1;
		for(int j = 1; j < i; j++){
			ncr[i][j] = (ncr[i-1][j-1] + ncr[i-1][j]) % mod;
		}
	}
	int ans = 0;
	function<void(int, int, int)> get = [&](int pos, int rem, int n){
		if(pos == sz+1){
			if(rem == 0){
				int pot = 1;
				int reps = 1;
				for(int i = 1; i <= sz; ++i){
					reps = (lli)reps * ncr[freq[i]][sol[i]] % mod;
					pot = pot * power(i, sol[i], phi_mod) % phi_mod * power(i+1, freq[i] - sol[i], phi_mod) % phi_mod;
				}
				if(n & 1){
					ans -= reps * power(2, pot, mod) % mod;
					if(ans < 0) ans += mod;
				}else{
					ans += reps * power(2, pot, mod) % mod;
					if(ans >= mod) ans -= mod;
				}
			}
		}else{
			if(rem > acum[sz] - acum[pos-1]) return;
			for(int xi = 0; xi <= freq[pos]; ++xi){
				if(rem-xi < 0) break;
				sol[pos] = xi;
				get(pos+1, rem-xi, n);
				sol[pos] = 0;
			}
		}
	};
	for(int n = 0; n <= primes.size(); ++n){
		get(1, n, n);
	}
	ans = (lli)ans * 512 % modulo * power(512, phi_mod-1, mod) % modulo;
	cout << ans << "\n";
	return 0;
}