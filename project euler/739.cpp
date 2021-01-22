#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9 + 7;

int main(){
	int n = 1e8;
	vector<int> a(n);
	a[0] = 1, a[1] = 3;
	for(int i = 2; i < n; ++i){
		a[i] = a[i-1] + a[i-2];
		if(a[i] >= mod) a[i] -= mod;
	}
	vector<int> fact(2*n+1, 1), inv(2*n+1, 1), invfact(2*n+1, 1);
	for(lli i = 2; i <= 2*n; ++i){
		fact[i] = i * fact[i-1] % mod;
		inv[i] = mod - (mod / i) * inv[mod % i] % mod;
		invfact[i] = (lli)inv[i] * invfact[i-1] % mod;
	}
	auto ncr = [&](int n, int k){
		if(k < 0 || k > n) return 0ll;
		return (lli)fact[n] * invfact[k] % mod * invfact[n-k] % mod;
	};
	lli ans = 0;
	for(int i = 0; i < n; ++i){
		ans += (ncr(i+n-2, n-2) - ncr(i+n-2, n-1)) * a[n-1-i] % mod;
		if(ans >= mod) ans -= mod;
		if(ans < 0) ans += mod;
	}
	cout << ans << "\n";
	return 0;
}