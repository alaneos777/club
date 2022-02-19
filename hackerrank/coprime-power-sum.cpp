#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9 + 7;

lli powerMod(lli a, lli b){
	if(a == 1) return 1;
	a %= mod;
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

const int M = 10;
vector<lli> B(M+1, 1), fact(M+2, 1), inv(M+2, 1), invfact(M+2, 1);

lli ncr(int n, int k){
	if(k < 0 || k > n) return 0;
	return fact[n] * invfact[k] % mod * invfact[n-k] % mod;
}

lli P(lli n, int p){
	lli ans = 0;
	if(n <= p){
		for(int i = 1; i <= n; ++i){
			ans += powerMod(i, p);
			if(ans >= mod) ans -= mod;
		}
	}else{
		for(int k = 0; k <= p; ++k){
			ans += invfact[p+1-k] * B[k] % mod * powerMod(n, p+1-k) % mod;
			if(ans >= mod) ans -= mod;
		}
		ans = ans * fact[p] % mod;
	}
	return ans;
}

inline lli Abs(__int128_t n){
	return n > 0 ? n : -n;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	for(lli i = 2; i <= M+1; ++i){
		fact[i] = i * fact[i-1] % mod;
		inv[i] = mod - (mod / i) * inv[mod % i] % mod;
		invfact[i] = inv[i] * invfact[i-1] % mod;
	}
	for(int n = 1; n <= M; ++n){
		for(int k = 0; k <= n-1; ++k){
			B[n] -= ncr(n, k) * B[k] % mod * inv[n-k+1] % mod;
			if(B[n] < 0) B[n] += mod;
		}
	}
	for(int i = 0; i <= M; ++i){
		B[i] = B[i] * invfact[i] % mod;
	}
	int q;
	cin >> q;
	while(q--){
		int n, k; lli m;
		cin >> n >> k >> m;
		vector<lli> s;
		for(int i = 0; i < n; ++i){
			lli si;
			cin >> si;
			s.push_back(si);
		}
		n = s.size();
		int lim = sqrt(m)/10;
		vector<vector<int>> mem(n+1, vector<int>(lim+1, -1));
		function<lli(int, lli)> f = [&](int pos, lli m) -> lli{
			if(pos == n){
				return P(m, k);
			}else{
				if(m <= lim && mem[pos][m] != -1) return mem[pos][m];
				lli p = s[pos];
				lli ans = f(pos+1, m);
				if(m >= p){
					ans -= powerMod(p, k) * f(pos+1, m/p) % mod;
					if(ans < 0) ans += mod;
				}
				if(m <= lim) mem[pos][m] = ans;
				return ans;
			}
		};
		cout << f(0, m) << "\n";
	}
	return 0;
}