#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli m0 = 29, m1 = 34483;

lli power(lli a, lli b, lli m){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans;
}

template<int mod>
lli solve(int n, int m, int k){
	vector<int> fact(mod, 1), inv(mod, 1), invfact(mod, 1);
	for(lli i = 2; i < mod; ++i){
		fact[i] = i * fact[i-1] % mod;
		inv[i] = mod - (mod / i) * inv[mod % i] % mod;
		invfact[i] = (lli)inv[i] * invfact[i-1] % mod;
	}
	auto ncr0 = [&](int n, int k){
		if(k < 0 || k > n) return 0ll;
		return (lli)fact[n] * invfact[k] % mod * invfact[n-k] % mod;
	};
	auto ncr = [&](int n, int k){
		lli ans = 1;
		while(n > 0 || k > 0){
			ans = ans * ncr0(n%mod, k%mod) % mod;
			n /= mod;
			k /= mod;
		}
		return ans;
	};
	lli ans = 0;
	for(lli i = 0; i*(m+1) <= k; ++i){
		lli pi = ncr(n, i);
		if(i & 1) pi = (mod - pi) % mod;
		int j = k - i*(m+1);
		lli pj = ncr(j + n-1, n-1);
		ans += pi*pj % mod;
		if(ans >= mod) ans -= mod;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m, k;
	cin >> n >> m >> k;
	lli a0 = solve<m0>(n, m, k);
	lli a1 = solve<m1>(n, m, k);
	lli t = power(m0, m1-2, m1) * (a1 - a0) % m1;
	if(t < 0) t += m1;
	lli x = a0 + m0 * t;
	cout << x << "\n";
	return 0;
}