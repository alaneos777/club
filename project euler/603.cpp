#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9 + 7;

const lli inv_2 = (mod+1)/2;

lli power(lli a, lli b){
	b %= mod-1;
	if(b < 0) b += mod-1;
	lli ans = 1;
	while(b){
		if(b&1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

auto sieve(int n){
	vector<int> primes;
	vector<bool> is(n+1, true);
	for(int i = 2; i <= n; ++i){
		if(is[i]) primes.push_back(i);
		for(int p : primes){
			int d = i*p;
			if(d > n) break;
			is[d] = false;
			if(i%p == 0) break;
		}
	}
	return primes;
}

const auto primes = sieve(2e7);

int main(){
	int n = 1e6; lli k = 1e12;
	assert(n < primes.size());
	string S;
	for(int i = 0; i < n; ++i){
		S += to_string(primes[i]);
	}
	int len = S.size();

	lli x = (power(10, len*k) - 1) * power(power(10, len) - 1, -1) % mod;
	lli y = (k%mod - 1 - (k%mod)*power(10, len) % mod + power(10, len*k)) * power(power(10, len) - 1, -2) % mod;
	lli z = k % mod;
	lli w = (k % mod) * ((k-1) % mod) % mod * inv_2 % mod;
	if(y < 0) y += mod;

	lli ans = 0;
	lli ten_pw = power(10, len), ten_inv = power(10, -1);
	for(int i = 0; i < len; ++i){
		lli a = (i+1) * (ten_pw * x % mod - z) % mod;
		lli b = len * (ten_pw * y % mod - w) % mod;
		ans += (S[i]-'0') * (a+b) % mod;
		if(ans >= mod) ans -= mod;
		if(ans < 0) ans += mod;
		ten_pw = ten_pw * ten_inv % mod;
	}
	ans = ans * power(9, -1) % mod;
	cout << ans << "\n";
	return 0;
}