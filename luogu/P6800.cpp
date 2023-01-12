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
poly bluestein(poly A, int w){
	int n = A.size(), m = nearestPowerOfTwo(2*n-1);
	int w1 = 1, w2 = 1;
	poly p(m), q(m), b(n);
	for(int k = 0; k < n; ++k, w2 = (lli)w2*w1 % mod, w1 = (lli)w1*w % mod){
		b[k] = w2;
		p[n-1-k] = A[k] * powerMod<mod>(b[k], mod-2) % mod;
		q[k] = b[k];
	}
	for(int k = n; k < 2*n-1; ++k, w2 = (lli)w2*w1 % mod, w1 = (lli)w1*w % mod){
		q[k] = w2;
	}
	ntt<mod, g>(p, 1), ntt<mod, g>(q, 1);
	for(int i = 0; i < m; i++)
		p[i] = (lli)p[i] * q[i] % mod;
	ntt<mod, g>(p, -1);
	for(int k = 0; k < n; ++k)
		A[k] = p[k+n-1] * powerMod<mod>(b[k], mod-2) % mod;
	return A;
}

const int mod = 998244353, g = 3;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, c, m;
	cin >> n >> c >> m;
	vector<int> a(n);
	for(int& ai : a){
		cin >> ai;
	}
	a.resize(max(m, n));
	a = bluestein<mod, g>(a, c);
	for(int i = 0; i < m; ++i){
		if(i) cout << " ";
		cout << a[i];
	}
	cout << "\n";
	return 0;
}