#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli mod = 1e16;

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

int main(){
	vector<int> S = sieve(5000);
	int sum_S = 0;
	int sz = S.size();
	for(int p : S){
		sum_S += p;
	}
	vector<int> primes = sieve(sum_S);

	vector<vector<lli>> dp(2, vector<lli>(sum_S+1));

	for(int n = 0; n < sz; ++n){
		dp[n&1][0] = 1;
		for(int sum = 1; sum <= sum_S; ++sum){
			lli ans = 0;
			if(n == 0){
				if(sum == S[n]){
					ans = 1;
				}
			}else{
				ans = dp[(n-1)&1][sum];
				if(sum - S[n] >= 0){
					ans += dp[(n-1)&1][sum - S[n]];
				}
			}
			if(ans >= mod) ans -= mod;
			dp[n&1][sum] = ans;
		}
	}

	lli ans = 0;
	for(int p : primes){
		ans += dp[(sz-1)&1][p];
		if(ans >= mod) ans -= mod;
	}
	cout << ans << "\n";
	return 0;
}