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
		lli nrev = powerMod(n, prime-2, prime);
		for(int i = 0; i < n; ++i)
			X[i] = X[i] * nrev % prime;
	}
}

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

const int p = 998244353, g = 3;

const int M = 1e6;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	vector<int> fact(M+1, 1), inv(M+1, 1), invfact(M+1, 1), pw(M+1, 1);
	pw[1] = 2;
	for(int i = 2; i <= M; ++i){
		fact[i] = (lli)fact[i-1] * i % p;
		inv[i] = p - (p / i) * (lli)inv[p % i] % p;
		invfact[i] = (lli)invfact[i-1] * inv[i] % p;
		pw[i] = pw[i-1] * 2ll % p;
	}
	int n, k, q;
	cin >> n >> k;
	map<int, int> freq;
	for(int i = 0; i < n; ++i){
		int ai;
		cin >> ai;
		freq[ai]++;
	}
	vector<vector<int>> S(k);
	vector<int> red(k);
	for(int j = 0; j < k; ++j){
		cin >> red[j];
		int unique = 0, repeated = 0;
		for(auto par : freq){
			if(par.first < red[j]){
				if(par.second == 1) unique++;
				else repeated++;
			}
		}
		vector<int> P(unique+1), Q(2*repeated+1);
		for(int i = 0; i <= unique; ++i){
			P[i] = (lli)fact[unique] * invfact[i] % p * invfact[unique - i] % p * pw[i] % p;
		}
		for(int i = 0; i <= 2*repeated; ++i){
			Q[i] = (lli)fact[2*repeated] * invfact[i] % p * invfact[2*repeated - i] % p;
		}
		S[j] = convolution<p, g>(P, Q);
	}
	cin >> q;
	while(q--){
		int qi;
		cin >> qi;
		int ans = 0;
		for(int j = 0; j < k; ++j){
			int idx = qi/2-1-red[j];
			ans += 0 <= idx && idx < S[j].size() ? S[j][idx] : 0;
			if(ans >= p) ans -= p;
		}
		cout << ans << "\n";
	}
	return 0;
}