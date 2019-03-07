#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli mod = 1e9 + 7;

lli powerMod(lli a, lli b){
	lli ans = 1;
	a %= mod;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

int main(){
	lli a = 1e7, n = 1000000000000ll;
	vector<lli> inverse(a+1);
	inverse[1] = 1;
	for(lli i = 2; i <= a; ++i){
		inverse[i] = mod - (mod / i) * inverse[mod % i] % mod;
	}
	lli ans = 0;
	if(ans < 0) ans += mod;
	lli alt = (a & 1) ? 1 : -1;
	lli comb = 1;
	for(lli j = 0; j < a; ++j){
		lli geo = 1;
		if(j == 0) geo = 1;
		else if(j == 1) geo = (n + 1) % mod;
		else geo = (powerMod(j, n + 1) - 1) * inverse[j - 1] % mod;
		lli term = comb * geo % mod * alt;
		ans += term;
		if(ans >= mod) ans -= mod;
		if(ans < 0) ans += mod;
		comb = comb * (a - j) % mod * inverse[j + 1] % mod;
		alt = -alt;
	}
	cout << ans << "\n";
	return 0;
}