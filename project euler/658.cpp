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
	lli m = 10000000ll, n = 1000000000000ll;
	vector<lli> inverse(m+10);
	inverse[1] = 1;
	for(lli i = 2; i <= m+9; ++i){
		inverse[i] = mod - (mod / i) * inverse[mod % i] % mod;
	}

	vector<lli> P(m+2), Q(m+1);
	lli comb = 1;
	for(lli i = 0; i <= m+1; ++i){
		P[i] = comb;
		comb = comb * (m + 1 - i) % mod * inverse[i + 1] % mod;
	}
	if(m & 1) P[0]--;
	else P[0]++;
	if((m & 1) == 0){
		for(lli i = 0; i <= m+1; ++i){
			P[i] = (mod - P[i]) % mod;
		}
	}

	Q[m] = P[m+1];
	for(lli i = m; i >= 1; --i){
		Q[i-1] = -2ll*Q[i]%mod + P[i];
		if(Q[i-1] < 0) Q[i-1] += mod;
	}

	lli ans = 0;
	lli alt = 1;
	for(lli j = 0; j < m; ++j){
		lli geo = 1;
		if(j == 0) geo = 1;
		else if(j == 1) geo = (n + 1) % mod;
		else geo = (powerMod(j, n + 1) - 1) * inverse[j - 1] % mod;
		lli term = (Q[j] + alt) * geo % mod * alt;
		ans += term;
		if(ans >= mod) ans -= mod;
		if(ans < 0) ans += mod;
		alt = -alt;
	}
	cout << ans << "\n";
	return 0;
}