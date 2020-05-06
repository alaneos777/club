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

const int M = 1e6;
const int mod_digits = int(1e5)/8; //12500 = 2^2 * 5^5
const int target = 65432/8;
const lli mod = lli(1e16) + 61;
auto primes = sieve(M);

int potInFactorial(int n, int p){
	int ans = 0;
	while(n /= p) ans += n;
	return ans;
}

lli dp[2][mod_digits];

int main(){
	primes.erase(remove(primes.begin(), primes.end(), 2), primes.end());
	primes.erase(remove(primes.begin(), primes.end(), 5), primes.end());
	vector<int> pots;
	for(int p : primes){
		pots.push_back(potInFactorial(M, p));
	}

	dp[0][1] = 1;
	for(int idx = 1; idx <= primes.size(); ++idx){
		for(int r = 0; r < mod_digits; ++r){
			dp[idx & 1][r] = 0;
		}
		int p = primes[idx-1] % mod_digits;
		for(int r = 0; r < mod_digits; ++r){
			int p_pow = 1;
			for(int i = 0; i <= pots[idx-1]; ++i){
				lli & nxt = dp[idx & 1][r * p_pow % mod_digits];
				nxt += dp[(idx-1) & 1][r];
				if(nxt >= mod) nxt -= mod;
				p_pow = p_pow * p % mod_digits;
			}
		}
	}
	cout << dp[primes.size() & 1][target] << "\n";
	return 0;
}