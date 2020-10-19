#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;
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
	int n = 1e7, k = 4e6;
	--k;
	lli ans = 0;
	lli comb = 1;
	for(int j = 0; j <= k; ++j){
		lli term = comb * power(k+1 - j, n) % mod;
		if(j & 1) ans -= term;
		else ans += term;
		if(ans >= mod) ans -= mod;
		if(ans < 0) ans += mod;
		comb = comb * (n+1 - j) % mod * power(j+1, mod-2) % mod;
	}
	cout << ans << "\n";
	return 0;
}