#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli n = 1e13, m = 1e12, d = 1e4;
const lli mod = 1e9 - 63;

const int M = 8e5;
vector<int> fact, inv, invfact;

lli ncr(lli n, lli k){
	if(k < 0 || k > n) return 0;
	return (lli)fact[n] * invfact[k] % mod * invfact[n-k] % mod;
}

lli Ncr(lli n, lli k){
	lli ans = 1;
	while(n && k){
		lli n0 = n % mod, k0 = k % mod;
		ans = ans * ncr(n0, k0) % mod;
		n /= mod, k /= mod;
	}
	return ans;
}

int main(){
	fact.resize(M+1, 1), inv.resize(M+1, 1), invfact.resize(M+1, 1);
	for(lli i = 2; i <= M; ++i){
		fact[i] = i * fact[i-1] % mod;
		inv[i] = mod - (mod / i) * inv[mod % i] % mod;
		invfact[i] = (lli)inv[i] * invfact[i-1] % mod;
	}
	lli ans = Ncr(n, d) * Ncr(n - d - 1, m - d - 1) % mod;
	cout << ans << "\n";
	return 0;
}