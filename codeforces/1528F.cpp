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

const int M = 1e5 + 10;
vector<int> fact(M+1, 1), inv(M+1, 1), invfact(M+1, 1);

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	for(lli i = 2; i <= M; ++i){
		fact[i] = i * fact[i-1] % p;
		inv[i] = p - (p / i) * inv[p % i] % p;
		invfact[i] = (lli)inv[i] * invfact[i-1] % p;
	}
	int n, k;
	cin >> n >> k;
	vector<int> P(k+1), Q(k+1);
	for(int i = 0; i <= k; ++i){
		P[i] = powerMod(i, k, p) * invfact[i] % p;
		Q[i] = invfact[i];
		if(i & 1) Q[i] = p - Q[i];
	}
	vector<int> s2 = convolution<p,g>(P, Q);
	s2.resize(k+1);
	lli ans = 0;
	lli ncr = n % p;
	for(int i = 1; i <= k; ++i){
		ans += (lli)s2[i] * fact[i] % p * ncr % p * powerMod((n + 1) % p, n - i, p) % p;
		if(ans >= p) ans -= p;
		lli num = n%p - i;
		if(num < 0) num += p;
		ncr = ncr * num % p * inv[i+1] % p;
	}
	cout << ans << "\n";
	return 0;
}