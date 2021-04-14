#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

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

const int p = 998244353, g = 3;

vector<int> inversePolynomial(const vector<int> & A){
	vector<int> R(1, powerMod(A[0], p - 2, p));
	while(R.size() < A.size()){
		size_t c = 2 * R.size();
		R.resize(c);
		vector<int> R2 = R;
		vector<int> a(min(c, A.size()));
		for(int i = 0; i < a.size(); ++i)
			a[i] = A[i];
		R2 = convolution<p, g>(R2, R2);
		R2.resize(c);
		R2 = convolution<p, g>(R2, a);
		for(int i = 0; i < c; ++i){
			R[i] = R[i] + R[i] - R2[i];
			if(R[i] < 0) R[i] += p;
			if(R[i] >= p) R[i] -= p;
		}
	}
	R.resize(A.size());
	return R;
}

const int M = 1e5 + 10;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	vector<int> fact(M+2, 1), inv(M+2, 1), invfact(M+2, 1);
	for(lli i = 2; i <= M+1; ++i){
		fact[i] = i * fact[i-1] % p;
		inv[i] = p - (p / i) * inv[p % i] % p;
		invfact[i] = (lli)inv[i] * invfact[i-1] % p;
	}
	vector<int> P_den(M+1);
	for(int i = 0; i <= M; ++i){
		P_den[i] = invfact[i+1];
	}
	P_den = inversePolynomial(P_den);
	int t;
	cin >> t;
	while(t--){
		int n;
		cin >> n;
		vector<int> a(n);
		lli den = 1;
		int mini = 2e9;
		for(int& ai : a){
			cin >> ai;
			den = den * (ai+1) % p;
			mini = min(mini, ai);
		}
		if(mini == 0){
			cout << "0\n";
			continue;
		}
		function<vector<int>(int, int, int)> mult = [&](int s, int l, int r){
			if(l == r){
				int p0 = a[l] + s;
				if(p0 >= p) p0 -= p;
				if(p0 < 0) p0 += p;
				return vector<int>{p0, p-2};
			}else{
				int m = (l + r) >> 1;
				return convolution<p, g>(mult(s, l, m), mult(s, m+1, r));
			}
		};
		vector<int> P = mult(1, 0, n-1);
		vector<int> Q = mult(-1, 0, n-1);
		int l1 = (mini + 1) / 2;
		int l2 = (mini - 1) / 2;
		vector<int> R(P_den.begin(), P_den.begin() + n+2);
		vector<int> F(n+2), G(n+2);
		lli l1_pow = l1 + 1, l2_pow = l2 + 1;
		for(int i = 0; i <= n+1; ++i){
			F[i] = l1_pow * invfact[i+1] % p;
			G[i] = l2_pow * invfact[i+1] % p;
			l1_pow = l1_pow * (l1 + 1) % p;
			l2_pow = l2_pow * (l2 + 1) % p;
		}
		F = convolution<p, g>(F, R);
		G = convolution<p, g>(G, R);
		F.resize(n+2);
		G.resize(n+2);
		lli ans = 0;
		for(int i = 0; i <= n; ++i){
			lli term = (lli)P[i] * F[i+1] % p - (lli)Q[i] * G[i+1] % p;
			if(term < 0) term += p;
			term = term * fact[i+1] % p;
			ans += term;
			if(ans >= p) ans -= p;
		}
		ans = ans * powerMod(den, -1, p) % p;
		cout << ans << "\n";
	}
	return 0;
}