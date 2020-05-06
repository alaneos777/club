#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli mod = 1e9 + 7;

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

auto divsSieve(int n){
	vector<vector<int>> divs(n+1);
	for(int i = 1; i <= n; ++i){
		for(int j = i; j <= n; j += i){
			divs[j].push_back(i);
		}
	}
	return divs;
}

const auto primes = sieve(1e8);
const auto divs = divsSieve(9);

int main(){
	vector<int> digits;
	for(int i = primes.size()-1; i >= 0; --i){
		int n = primes[i];
		while(n){
			if(n%10) digits.push_back(n%10);
			n /= 10;
		}
	}
	lli ans = 0;
	lli m = 1;
	vector<lli> freq(10);
	for(int g_n : digits){
		int sz = divs[g_n].size();
		lli old = ans;
		ans = 0;
		for(int d : divs[g_n]){
			ans += old;
			if(ans >= mod) ans -= mod;
			for(int i = 1; i < d; ++i){
				ans += freq[i];
				if(ans >= mod) ans -= mod;
			}
		}
		//Update frequencies
		for(int i = 0; i <= 9; ++i){
			freq[i] = freq[i] * sz % mod;
		}
		for(int d : divs[g_n]){
			freq[d] += m;
			if(freq[d] >= mod) freq[d] -= mod;
		}
		m = m * sz % mod;
	}
	cout << ans << "\n";
	return 0;
}