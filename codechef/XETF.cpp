#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9 + 7;
const int M = 1e4 + 10;

lli power(lli a, lli b){
	a %= mod;
	b %= mod-1;
	if(b < 0) b += mod-1;
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

auto factorize(lli n){
	vector<lli> f;
	for(lli p = 2; p*p <= n; ++p){
		int e = 0;
		while(n % p == 0){
			n /= p;
			e++;
		}
		if(e) f.emplace_back(p);
	}
	if(n > 1) f.emplace_back(n);
	return f;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	vector<int> fact(M+1, 1), inv(M+1, 1), invfact(M+1, 1);
	for(lli i = 2; i <= M; ++i){
		fact[i] = i * fact[i-1] % mod;
		inv[i] = mod - (mod / i) * inv[mod % i] % mod;
		invfact[i] = (lli)inv[i] * invfact[i-1] % mod;
	}
	auto ncr = [&](int n, int k) -> lli{
		if(k < 0 || k > n) return 0;
		return (lli)fact[n] * invfact[k] % mod * invfact[n-k] % mod;
	};
	vector<int> B(M);
	B[0] = 1;
	for(int n = 1; n < M; ++n){
		B[n] = 1;
		for(int k = 0; k < n; ++k){
			B[n] -= ncr(n, k) * B[k] % mod * inv[n-k+1] % mod;
			if(B[n] < 0) B[n] += mod;
		}
	}
	int t;
	cin >> t;
	while(t--){
		lli n; int k;
		cin >> n >> k;
		lli ans = 0;
		auto f = factorize(n);
		for(int j = 1; j <= k+1; ++j){
			lli term = ncr(k+1, j) * inv[k+1] % mod * B[k+1-j] % mod * power(n, j) % mod;
			for(lli p : f){
				term = term * (1 - power(p, k-j)) % mod;
				if(term < 0) term += mod;
			}
			ans += term;
			if(ans >= mod) ans -= mod;
		}
		cout << ans << "\n";
	}
	return 0;
}