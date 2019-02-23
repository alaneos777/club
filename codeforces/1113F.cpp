#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli mod = 1e9 + 7;
const lli M = 1.5e6;

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

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	vector<lli> fact(M+1, 1), invfact(M+1, 1);
	for(lli i = 1; i <= M; ++i){
		fact[i] = fact[i-1] * i % mod;
		invfact[i] = powerMod(fact[i], mod-2);
	}
	lli n, m, a, b, ans = 0;
	cin >> n >> m >> a >> b;
	for(lli k = 1; k <= n-1 && k <= m; ++k){
		lli curr = fact[n-2] * invfact[n-k-1] % mod;
		curr = curr * (k+1) % mod;
		curr = curr * powerMod(n, n-k-2) % mod;
		curr = curr * fact[m-1] % mod;
		curr = curr * invfact[k-1] % mod;
		curr = curr * invfact[m-k] % mod;
		curr = curr * powerMod(m, n-k-1) % mod;
		ans += curr;
		if(ans >= mod) ans -= mod;
	}
	cout << ans << "\n";
	return 0;
}