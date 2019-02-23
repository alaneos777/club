#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int nearestPowerOfTwo(int n){
	int ans = 1;
	while(ans < n) ans <<= 1;
	return ans;
}

int inverse(int a, int n){
	int r0 = a, r1 = n, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	if(s0 < 0) s0 += n;
	return s0;
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

template<int prime, int gen>
void ntt(vector<int> & X, int inv){
	int n = X.size();
	for(int i = 1, j = 0; i < n - 1; ++i){
		for(int k = n >> 1; (j ^= k) < k; k >>= 1);
		if(i < j) swap(X[i], X[j]);
	}
	vector<lli> wp(n>>1, 1);
	for(int k = 1; k < n; k <<= 1){
		lli wk = powerMod(gen, inv * (prime - 1) / (k<<1), prime);
		for(int j = 1; j < k; ++j)
			wp[j] = wp[j - 1] * wk % prime;
		for(int i = 0; i < n; i += k << 1){
			for(int j = 0; j < k; ++j){
				int u = X[i + j], v = X[i + j + k] * wp[j] % prime;
				X[i + j] = u + v < prime ? u + v : u + v - prime;
				X[i + j + k] = u - v < 0 ? u - v + prime : u - v;
			}
		}
	}
	if(inv == -1){
		lli nrev = inverse(n, prime);
		for(int i = 0; i < n; ++i)
			X[i] = X[i] * nrev % prime;
	}
}

const int mod = 1e9 + 7;

template<int prime, int gen>
vector<int> convolution(vector<int> A, vector<int> B){
	int sz = A.size() + B.size() - 1;
	int size = nearestPowerOfTwo(sz);
	A.resize(size), B.resize(size);
	ntt<prime, gen>(A, 1), ntt<prime, gen>(B, 1);
	for(int i = 0; i < size; i++)
		A[i] = (lli)A[i] * B[i] % prime;
	ntt<prime, gen>(A, -1);
	A.resize(sz);
	return A;
}

const int a = 998244353, b = 985661441, c = 754974721;
const lli a_b = inverse(a, b), a_c = inverse(a, c), b_c = inverse(b, c);
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
		D[i] = x1 + a*(x2 + (lli)x3*b % mod) % mod;
		if(D[i] >= mod) D[i] -= mod;
		if(D[i] < 0) D[i] += mod;
	}
	return D;
}

const int M = 1e6 + 100;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	vector<int> fact(M+1, 1), inv(M+1, 1), invfact(M+1, 1);
	for(int i = 2; i <= M; ++i){
		fact[i] = (lli)fact[i-1] * i % mod;
		inv[i] = mod - (lli)(mod / i) * inv[mod % i] % mod;
		invfact[i] = (lli)invfact[i-1] * inv[i] % mod;
	}
	int t, n, x, r;
	cin >> t;
	while(t--){
		cin >> n >> x >> r;
		vector<int> p(r), q(r);
		for(int i = 0; i < r; ++i){
			p[i] = powerMod(i, r, mod) * invfact[i] % mod;
			q[i] = invfact[i];
			if(i & 1) q[i] = (mod - q[i]) % mod;
		}
		vector<int> stirling = (r == 0 ? vector<int>{} : conv(p, q));
		stirling.resize(r);
		stirling.push_back(1);

		p = vector<int>(r+1), q = vector<int>(r+1);
		int comb = 1;
		for(int i = 0; i <= r; ++i){
			p[i] = (lli)comb * powerMod(x, n+1-i, mod) % mod;
			q[i] = powerMod(x-1, -i-1, mod);
			if(i & 1) q[i] = (mod - q[i]) % mod;
			comb = (lli)comb * (n+1-i) % mod * inv[i+1] % mod;
		}
		vector<int> f = conv(p, q);
		f.resize(r+1);
		for(int j = 0; j <= r; ++j){
			f[j] = (lli)f[j] * fact[j] % mod;
			int term = (lli)fact[j] * powerMod(x-1, -j-1, mod) % mod;
			if(!(j & 1)) term = (mod - term) % mod;
			f[j] += term;
			if(f[j] >= mod) f[j] -= mod;
		}
		int ans = 0, x_pw = 1;
		for(int i = 0; i <= r; ++i){
			ans += (lli)stirling[i] * x_pw % mod * f[i] % mod;
			if(ans >= mod) ans -= mod;
			x_pw = (lli)x_pw * x % mod;
		}
		if(r == 0) ans = (ans + mod-1) % mod;
		cout << ans << "\n";
	}
	return 0;
}