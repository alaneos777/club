#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

const lli mod = 1000000009;

inline lli modula(lli n){
	while(n >= mod) n -= mod;
	while(n < 0) n += mod;
	return n;
}

lli powerMod(lli a, lli b){
	lli ans = 1;
	a %= mod;
	b %= mod-1;
	if(b < 0) b += mod-1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

const lli inv_2 = powerMod(2, mod-2);
const lli sqrt_5 = 383008016;
const int M = 1e5 + 10;
const lli Y1 = (1 + sqrt_5) * inv_2 % mod;
const lli Y2 = (1 + mod - sqrt_5) * inv_2 % mod;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	vector<lli> inv(M+1, 1);
	for(lli i = 2; i <= M; ++i){
		inv[i] = mod - (mod / i) * inv[mod % i] % mod;
	}
	int t;
	cin >> t;
	while(t--){
		lli n; int k;
		cin >> n >> k;
		lli ans = 0;
		lli comb = 1, prod = powerMod(Y1, k), alt = 1;
		lli d = Y2 * powerMod(Y1, -1) % mod;
		for(int j = 0; j <= k; ++j){
			ans += alt * comb * (prod == 1 ? (n+1)%mod : (powerMod(prod, n+1) - 1) % mod * powerMod(prod-1, -1) % mod) % mod;
			ans = modula(ans);
			comb = comb * (k - j) % mod * inv[j+1] % mod;
			prod = prod * d % mod;
			alt = -alt;
		}
		ans = ans * powerMod(sqrt_5, -k) % mod;
		cout << ans << "\n";
	}
	return 0;
}