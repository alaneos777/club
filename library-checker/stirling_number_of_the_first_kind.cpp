#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
using poly = vector<int>;

template<lli mod>
lli powerMod(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

int nearestPowerOfTwo(int n){
	int ans = 1;
	while(ans < n) ans <<= 1;
	return ans;
}

template<int mod, int g>
void ntt(poly& a, int inv = 1){
	int n = a.size();
	for(int i = 1, j = 0; i < n-1; ++i){
		for(int k = n>>1; (j^=k) < k; k >>= 1);
		if(i < j) swap(a[i], a[j]);
	}
	for(int sz = 2; sz <= n; sz <<= 1){
		lli w_1 = powerMod<mod>(g, (mod-1)/sz);
		if(inv == -1) w_1 = powerMod<mod>(w_1, mod-2);
		vector<lli> w(sz/2, 1);
		for(int j = 1; j < sz/2; ++j){
			w[j] = w_1 * w[j-1] % mod;
		}
		for(int start = 0; start < n; start += sz){
			for(int j = 0; j < sz/2; ++j){
				int u = a[start + j], v = w[j] * a[start + sz/2 + j] % mod;
				a[start + j] = (u+v >= mod ? u+v-mod : u+v);
				a[start + sz/2 + j] = (u-v < 0 ? u-v+mod : u-v);
			}
		}
	}
	if(inv == -1){
		lli n_rev = powerMod<mod>(n, mod-2);
		for(int& ai : a){
			ai = ai * n_rev % mod;
		}
	}
}

template<int mod, int g>
poly convolution(poly a, poly b){
	int sz = a.size() + b.size() - 1;
	int SZ = nearestPowerOfTwo(sz);
	a.resize(SZ), b.resize(SZ);
	ntt<mod, g>(a, 1), ntt<mod, g>(b, 1);
	poly c(SZ);
	for(int i = 0; i < SZ; ++i){
		c[i] = (lli)a[i] * b[i] % mod;
	}
	ntt<mod, g>(c, -1);
	c.resize(sz);
	return c;
}

const int p = 998244353, g = 3;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	function<poly(int, int)> mult = [&](int l, int r){
		if(l == r) return poly{(p-l) % p, 1};
		int m = (l + r) / 2;
		return convolution<p,g>(mult(l, m), mult(m+1, r));
	};
	poly ans = n==0 ? poly{1} : mult(0, n-1);
	for(int si : ans){
		cout << si << " ";
	}
	cout << "\n";
	return 0;
}