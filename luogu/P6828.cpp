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
poly convolution(poly A, poly B){
	int sz = 2*A.size() - 1;
	int size = nearestPowerOfTwo(sz);
	A.resize(size), B.resize(size);
	ntt<mod, g>(A, 1), ntt<mod, g>(B, 1);
	for(int i = 0; i < size; i++)
		A[i] = (lli)A[i] * B[i] % mod;
	ntt<mod, g>(A, -1);
	A.resize(sz);
	return A;
}

const int a = 998244353, b = 985661441, c = 754974721;
const lli a_b = powerMod<b>(a, b-2), a_c = powerMod<c>(a, c-2), b_c = powerMod<c>(b, c-2);
const int mod = 1e9+7;
poly conv(const poly & A, const poly & B){
	poly P = convolution<a, 3>(A, B);
	poly Q = convolution<b, 3>(A, B);
	poly R = convolution<c, 11>(A, B);
	poly D(P.size());
	for(int i = 0; i < D.size(); ++i){
		int x1 = P[i] % a;
		if(x1 < 0) x1 += a;
		int x2 = a_b * (Q[i] - x1) % b;
		if(x2 < 0) x2 += b;
		int x3 = (a_c * (R[i] - x1) % c - x2) * b_c % c;
		if(x3 < 0) x3 += c;
		D[i] = x1 % mod + a*(x2 + (lli)x3*b % mod) % mod;
		if(D[i] >= mod) D[i] -= mod;
		if(D[i] < 0) D[i] += mod;
	}
	return D;
}

poly bluestein(poly A, int w){
	int n = A.size();
	int w1 = 1, w2 = 1;
	poly p(n), q(2*n-1), b(n);
	for(int k = 0; k < n; ++k, w2 = (lli)w2*w1 % mod, w1 = (lli)w1*w % mod){
		b[k] = powerMod<mod>(w2, mod-2);
		p[n-1-k] = (lli)A[k] * b[k] % mod;
		q[k] = w2;
	}
	for(int k = n; k < 2*n-1; ++k, w2 = (lli)w2*w1 % mod, w1 = (lli)w1*w % mod){
		q[k] = w2;
	}
	p = conv(p, q);
	for(int k = 0; k < n; ++k)
		A[k] = (lli)p[k+n-1] * b[k] % mod;
	return A;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, c, m;
	cin >> n >> c >> m;
	vector<int> a(n);
	for(int& ai : a){
		cin >> ai;
	}
	a.resize(max(m, n));
	a = bluestein(a, c);
	for(int i = 0; i < m; ++i){
		if(i) cout << " ";
		cout << a[i];
	}
	cout << "\n";
	return 0;
}