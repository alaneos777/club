#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;

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
void ntt(vector<int> & X, int inv){
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
vector<int> convolution(vector<int> A, vector<int> B){
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

const int mod = 1e9 + 7;

const int a = 998244353, b = 985661441, c = 754974721;
const lli a_b = powerMod(a, b-2, b), a_c = powerMod(a, c-2, c), b_c = powerMod(b, c-2, c);
vector<int> conv(const vector<int> & A, const vector<int> & B){
	vector<int> P = convolution<a, 3>(A, B);
	vector<int> Q = convolution<b, 3>(A, B);
	vector<int> R = convolution<c, 11>(A, B);
	vector<int> D(P.size());
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

const int M = 1e5;
vector<int> fact(M+1, 1), inv(M+1, 1), invfact(M+1, 1);

vector<int> shift(const vector<int> & a, int x0){
	int n = a.size();
	vector<int> p(n);
	vector<vector<int>> q(2, vector<int>(n));
	lli x_pow = 1;
	for(int k = 0; k < n; ++k){
		p[k] = (lli)fact[k] * a[k] % mod;
		q[k % 2][k] = x_pow * invfact[k] % mod;
		if(k % 2 == 1) x_pow = x_pow * x0 % mod;
	}
	reverse(q[0].begin(), q[0].end());
	reverse(q[1].begin(), q[1].end());
	vector<int> AA = conv(p, q[0]), BB = conv(p, q[1]);
	vector<int> A(n), B(n);
	for(int k = 0; k < n; ++k){
		A[k] = (lli)invfact[k] * AA[n-1 + k] % mod;
		B[k] = (lli)invfact[k] * BB[n-1 + k] % mod;
	}
	AA = conv(A, A), BB = conv(B, B);
	vector<int> ans(2*n - 1);
	for(int i = 0; i < 2*n - 1; ++i){
		ans[i] = AA[i] - (lli)x0 * BB[i] % mod;
		if(ans[i] < 0) ans[i] += mod;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	for(int i = 2; i <= M; ++i){
		fact[i] = (lli)i * fact[i-1] % mod;
		inv[i] = mod - (lli)(mod / i) * inv[mod % i] % mod;
		invfact[i] = (lli)inv[i] * invfact[i-1] % mod;
	}
	int t;
	cin >> t;
	while(t--){
		int n;
		cin >> n;
		vector<int> ans = {0, 1};
		for(int i = 0; i < n; ++i){
			int ai;
			cin >> ai;
			ans = shift(ans, ai);
		}
		cout << ans.size()-1 << "\n";
		for(int ai : ans){
			cout << ai << " ";
		}
		cout << "\n";
	}
	return 0;
}