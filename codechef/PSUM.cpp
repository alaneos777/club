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
vector<int> convolution(poly A, poly B){
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

vector<int> operator+(const vector<int> & a, const vector<int> & b){
	vector<int> c(max(a.size(), b.size()));
	for(int i = 0; i < c.size(); ++i){
		if(i < a.size()) c[i] = a[i];
		if(i < b.size()){
			c[i] += b[i];
			if(c[i] >= p) c[i] -= p;
		}
	}
	return c;
}

vector<int> operator*(const vector<int> & a, const vector<int> & b){
	vector<int> c = convolution<p,g>(a, b);
	c.resize(max(a.size(), b.size()));
	return c;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, s, k;
	cin >> n >> s >> k;
	vector<int> cost(n+1), val(n+1);
	for(int i = 1; i <= n; ++i){
		cin >> cost[i] >> val[i];
	}
	vector<int> fact(k+1, 1), inv(k+1, 1), invfact(k+1, 1);
	for(lli i = 2; i <= k; ++i){
		fact[i] = i * fact[i-1] % p;
		inv[i] = p - (p / i) * inv[p % i] % p;
		invfact[i] = (lli)inv[i] * invfact[i-1] % p;
	}
	vector<poly> exps(n+1, poly(k+1));
	for(int i = 1; i <= n; ++i){
		for(int j = 0; j <= k; ++j){
			exps[i][j] = powerMod(val[i], j, p) * invfact[j] % p;
		}
	}
	vector<vector<poly>> dp(2, vector<poly>(s+1));
	for(int i = 0; i <= n; ++i){
		for(int w = 0; w <= s; ++w){
			if(i == 0 || w == 0){
				dp[i&1][w] = poly{1};
			}else if(w >= cost[i]){
				dp[i&1][w] = dp[(i-1)&1][w] + exps[i] * dp[(i-1)&1][w-cost[i]];
			}else{
				dp[i&1][w] = dp[(i-1)&1][w];
			}
		}
	}
	cout << (lli)dp[n&1][s][k] * fact[k] % p << "\n";
	return 0;
}