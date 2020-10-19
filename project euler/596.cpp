#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;

const lli mod = 1e9 + 7;
const lli inv2 = (mod + 1) / 2;

lli g(lli n){
	n %= mod;
	return n * (n + 1) % mod * inv2 % mod;
}

lli f(lli n){
	lli ans = 0;
	lli m = sqrtl(n);
	for(lli i = 1, l = n/m; i <= l; ++i){
		ans += (n/i) % mod * i % mod;
		if(ans >= mod) ans -= mod;
	}
	for(lli i = 1; i < m; ++i){
		ans += (g(n/i) - g(n/(i+1))) * i % mod;
		if(ans >= mod) ans -= mod;
		if(ans < 0) ans += mod;
	}
	return ans;
}

const lli N = 1e8;

int main(){
	lli ans = (8*f(N*N)%mod - 32*f(N*N/4)%mod + 1) % mod;
	if(ans < 0) ans += mod;
	cout << ans << "\n";
	return 0;
}