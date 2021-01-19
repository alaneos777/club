#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9 + 7;

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

int main(){
	lli n = 1e16; int k = 1e8;
	vector<int> fact(k+1, 1), inv(k+1, 1), invfact(k+1, 1);
	for(lli i = 2; i <= k; ++i){
		fact[i] = fact[i-1] * i % mod;
		inv[i] = mod - (mod / i) * inv[mod % i] % mod;
		invfact[i] = (lli)inv[i] * invfact[i-1] % mod;
	}
	lli ans = 0;
	lli r = power(2, n/k);
	lli invr2 = power(r, mod-3);
	lli r_pow = power(r, k);
	for(int a = 0; 2*a <= k; ++a){
		ans += (lli)fact[k] * invfact[a] % mod * invfact[a] % mod * invfact[k-2*a] % mod * r_pow % mod;
		r_pow = r_pow * invr2 % mod;
		if(ans >= mod) ans -= mod;
	}
	cout << ans << "\n";
	return 0;
}