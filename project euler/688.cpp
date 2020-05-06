#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9 + 7;

const lli N = 1e16;

lli R(lli n){
	lli ans = 0;
	lli m = sqrt(n);
	for(lli k = 1, l = n/m; k <= l; ++k){
		ans += (n/k) % mod;
		if(ans >= mod) ans -= mod;
	}
	for(lli k = 1; k < m; ++k){
		ans += (n/k - n/(k+1)) % mod * k % mod;
		if(ans >= mod) ans -= mod;
		if(ans < 0) ans += mod;
	}
	return ans;
}

const lli inv2 = (mod + 1) / 2;

inline lli P1(lli n){
	n %= mod;
	return n * (n + 1) % mod * inv2 % mod;
}

lli S(lli n){
	lli ans = 0;
	lli m = sqrt(n);
	for(lli k = 1, l = n/m; k <= l; ++k){
		ans += k * P1(n/k) % mod;
		if(ans >= mod) ans -= mod;
	}
	for(lli k = 1; k < m; ++k){
		ans += (P1(n/k) - P1(n/(k+1))) * P1(k) % mod;
		if(ans >= mod) ans -= mod;
		if(ans < 0) ans += mod;
	}
	return ans;
}

int main(){
	lli ans = ((N + 1) % mod * (R(N) - R(N/2)) % mod - S(N) + 2*S(N/2)) % mod;
	if(ans < 0) ans += mod;
	cout << ans << "\n";
	return 0;
}