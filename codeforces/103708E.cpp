#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9+7;

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b&1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

const int M = 1e6;

int main(){
	vector<int> fact(M+1, 1), inv(M+1, 1), invfact(M+1, 1);
	for(lli i = 2; i <= M; ++i){
		fact[i] = i*fact[i-1] % mod;
		inv[i] = mod - (mod/i)*inv[mod%i] % mod;
		invfact[i] = (lli)inv[i] * invfact[i-1] % mod;
	}
	auto ncr = [&](int n, int r) -> lli{
		if(r < 0 || r > n) return 0;
		return (lli)fact[n] * invfact[r] % mod * invfact[n-r] % mod;
	};
	int n, m, k;
	cin >> n >> m >> k;
	lli ans = 0;
	for(int i = 0; i <= k; ++i){
		int term = ncr(k,i) * power(i, n) % mod;
		if((k-i)&1) ans -= term;
		else ans += term;
		if(ans >= mod) ans -= mod;
		if(ans < 0) ans += mod;
	}
	ans = ans * ncr(m,k) % mod;
	cout << ans << "\n";
	return 0;
}