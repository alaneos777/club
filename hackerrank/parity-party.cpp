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

const int p = 7340033, g = 3;
const int M = 2e5;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	vector<int> fact(M+1, 1), inv(M+1, 1), invfact(M+1, 1);
	for(lli i = 2; i <= M; ++i){
		fact[i] = i * fact[i-1] % p;
		inv[i] = p - (p/i) * inv[p%i] % p;
		invfact[i] = (lli)inv[i] * invfact[i-1] % p;
	}
	auto ncr = [&](int n, int k){
		if(k < 0 || k > n) return 0ll;
		return (lli)fact[n] * invfact[k] % p * invfact[n-k] % p;
	};
	int n, a, b, c;
	cin >> n >> a >> b >> c;
	vector<int> A(2*a+1), B(2*b+1);
	for(int	i = 0; i <= a; ++i){
		A[2*i] = ncr(a, i);
		if((a-i) % 2 == 1) A[2*i] = p - A[2*i];
	}
	for(int i = 0; i <= b; ++i){
		B[2*i] = ncr(b, i);
	}
	vector<int> P = convolution<p, g>(A, B);
	int ans = 0;
	for(int k = 0; k <= 2*(a+b); ++k){
		int term = (k+c-a-b)%p;
		if(term < 0) term += p;
		ans += P[k] * powerMod(term, n, p) % p;
		if(ans >= p) ans -= p;
	}
	ans = ans * powerMod(2, -(a+b), p) % p;
	cout << ans << "\n";
	return 0;
}