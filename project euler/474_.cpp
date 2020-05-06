#include <bits/stdc++.h>
using namespace std;
using lli = __int128_t;

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
const lli mod = lli(1e16) + 61;
auto primes = sieve(M);

int potInFactorial(int n, int p){
	int ans = 0;
	while(n /= p) ans += n;
	return ans;
}

int main(){
	lli ans = 1;
	for(int p : primes){
		if(p == 2 || p == 3 || p == 5 || p == 401) continue;
		ans = ans * (1 + potInFactorial(M, p)) % mod;
	}
	ans = ans * 249997 % mod;
	cout << (int64_t)ans << "\n";
	return 0;
}