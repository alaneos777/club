#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;
const lli mod = 1e8 + 7;

vector<int> fact(mod, 1), inv(mod, 1), invfact(mod, 1);

lli ncr2(int n, int k){
	if(k < 0 || k > n) return 0;
	return (lli)fact[n] * invfact[k] % mod * invfact[n-k] % mod;
}

lli ncr(lli n, lli k){
	if(k < 0 || k > n) return 0;
	lli ans = 1;
	while(n || k){
		lli a = n % mod, b = k % mod;
		n /= mod, k /= mod;
		ans = ans * ncr2(a, b) % mod;
		if(ans == 0) break;
	}
	return ans;
}

lli f(lli n){
	lli ans = 8ll * ncr(2*n, n) % mod - 3ll * (n % mod) * (n % mod) % mod - 2ll * (n % mod) % mod - 7ll;
	ans %= mod;
	if(ans < 0) ans += mod;
	return ans;
}

int main(){
	for(int i = 2; i < mod; ++i){
		fact[i] = (lli)i * fact[i-1] % mod;
		inv[i] = mod - (lli)(mod / i) * inv[mod % i] % mod;
		invfact[i] = (lli)inv[i] * invfact[i-1] % mod;
	}
	int n = 90;
	vector<lli> fib = {0, 1};
	while(fib.size() <= n){
		fib.push_back(fib[fib.size()-1] + fib[fib.size()-2]);
	}
	lli ans = 0;
	for(int i = 2; i <= n; ++i){
		ans += f(fib[i]);
		if(ans >= mod) ans -= mod;
	}
	cout << ans << "\n";
	return 0;
}