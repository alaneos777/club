#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
using poly = vector<int>;

int nearestPowerOfTwo(int n){
	int ans = 1;
	while(ans < n) ans <<= 1;
	return ans;
}

lli powerMod(lli b, lli e, lli m){
	lli ans = 1;
	e %= m-1;
	if(e < 0) e += m-1;
	while(e){
		if(e & 1) ans = ans * b % m;
		e >>= 1;
		b = b * b % m;
	}
	return ans;
}

template<int p, int g>
void ntt(poly & X, int inv){
	int n = X.size();
	for(int i = 1, j = 0; i < n - 1; ++i){
		for(int k = n >> 1; (j ^= k) < k; k >>= 1);
		if(i < j) swap(X[i], X[j]);
	}
	vector<lli> wp(n>>1, 1);
	for(int k = 1; k < n; k <<= 1){
		lli wk = powerMod(g, inv * (p - 1) / (k<<1), p);
		for(int j = 1; j < k; ++j)
			wp[j] = wp[j - 1] * wk % p;
		for(int i = 0; i < n; i += k << 1){
			for(int j = 0; j < k; ++j){
				int u = X[i + j], v = X[i + j + k] * wp[j] % p;
				X[i + j] = u + v < p ? u + v : u + v - p;
				X[i + j + k] = u - v < 0 ? u - v + p : u - v;
			}
		}
	}
	if(inv == -1){
		lli nrev = powerMod(n, p - 2, p);
		for(int i = 0; i < n; ++i)
			X[i] = X[i] * nrev % p;
	}
}

template<int p, int g>
poly convolution(poly A, poly B){
	int sz = A.size() + B.size() - 1;
	int size = nearestPowerOfTwo(sz);
	A.resize(size), B.resize(size);
	ntt<p, g>(A, 1), ntt<p, g>(B, 1);
	for(int i = 0; i < size; i++)
		A[i] = (lli)A[i] * B[i] % p;
	ntt<p, g>(A, -1);
	A.resize(sz);
	return A;
}

int mod, m;

const int a = 998244353, b = 985661441, c = 754974721;
const lli a_b = powerMod(a, b-2, b), a_c = powerMod(a, c-2, c), b_c = powerMod(b, c-2, c);
poly mult(const poly & A, const poly & B){
	poly P = convolution<a, 3>(A, B);
	poly Q = convolution<b, 3>(A, B);
	poly R = convolution<c, 11>(A, B);
	poly D(m);
	for(int i = 0; i < 2*m-1; ++i){
		int x1 = P[i] % a;
		if(x1 < 0) x1 += a;
		int x2 = a_b * (Q[i] - x1) % b;
		if(x2 < 0) x2 += b;
		int x3 = (a_c * (R[i] - x1) % c - x2) * b_c % c;
		if(x3 < 0) x3 += c;
		int& pos = D[i%m];
		pos += (x1 % mod + a*(x2 + (lli)x3*b % mod) % mod) % mod;
		if(pos >= mod) pos -= mod;
		if(pos < 0) pos += mod;
	}
	return D;
}

poly power(poly a, lli b){
	poly ans(m);
	ans[0] = 1;
	while(b){
		if(b & 1) ans = mult(ans, a);
		b >>= 1;
		a = mult(a, a);
	}
	return ans;
}

poly shift(const poly& a, int k){
	poly b(m);
	for(int i = 0; i < m; ++i){
		int& pos = b[(i+k)%m];
		pos += a[i];
		if(pos >= mod) pos -= mod;
	}
	return b;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	lli n;
	int r;
	cin >> n >> m >> r >> mod;
	poly P(m);
	P[0] = P[1] = 1;
	P = shift(power(P, n), (m-r)%m);
	cout << (lli)P[0]*m%mod << "\n";
	return 0;
}