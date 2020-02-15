#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int nearestPowerOfTwo(int n){
	int ans = 1;
	while(ans < n) ans <<= 1;
	return ans;
}

const int M = 2e6 + 10;
vector<int> fact(M+1, 1), inv(M+1, 1), invfact(M+1, 1);

const int p = 998244353, g = 3;

lli powerMod(lli b, lli e){
	lli ans = 1;
	e %= p-1;
	if(e < 0) e += p-1;
	while(e){
		if(e & 1) ans = ans * b % p;
		e >>= 1;
		b = b * b % p;
	}
	return ans;
}

template<int prime, int gen>
void ntt(vector<int> & X, int rev){
	int n = X.size();
	for(int i = 1, j = 0; i < n - 1; ++i){
		for(int k = n >> 1; (j ^= k) < k; k >>= 1);
		if(i < j) swap(X[i], X[j]);
	}
	vector<lli> wp(n>>1, 1);
	for(int k = 1; k < n; k <<= 1){
		lli wk = powerMod(gen, rev * (prime - 1) / (k<<1));
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
	if(rev == -1){
		lli nrev = inv[n];
		for(int i = 0; i < n; ++i)
			X[i] = X[i] * nrev % prime;
	}
}

template<int prime, int gen>
vector<int> convolution(vector<int> & A, vector<int> & B){
	if(A.size() == 0) return B;
	if(B.size() == 0) return A;
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

vector<int> stirling(int n){
	if(n <= 300){
		vector<int> ans(n+1);
		ans[0] = 1;
		for(lli i = 1; i <= n; ++i){
			for(int j = i-1; j >= -1; --j){
				ans[j+1] = ans[j+1]*i%p + (j >= 0 ? ans[j] : 0);
				if(ans[j+1] >= p) ans[j+1] -= p;
			}
		}
		return ans;
	}else{
		int r = n/2;
		vector<int> first = move(stirling(r));
		vector<int> Q(r+1), P(r+1);
		for(int j = 0; j <= r; ++j){
			Q[j] = (lli)powerMod(r, j) * invfact[j] % p;
			P[r-j] = (lli)first[j] * fact[j] % p;
		}
		vector<int> second = convolution<p, g>(Q, P);
		second.resize(r+1);
		for(int j = 0; j <= r; ++j){
			second[j] = (lli)second[j] * invfact[r-j] % p;
		}
		reverse(second.begin(), second.end());
		vector<int> ans = convolution<p, g>(first, second);
		ans.resize(n+1);
		if(n & 1){
			for(int j = ans.size()-2; j >= -1; --j){
				ans[j+1] = (lli)ans[j+1] * n % p + (j >= 0 ? ans[j] : 0);
				if(ans[j+1] >= p) ans[j+1] -= p;
			}
		}
		return ans;
	}
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	for(int i = 2; i <= M; ++i){
		fact[i] = (lli)i * fact[i-1] % p;
		inv[i] = p - (lli)(p / i) * inv[p % i] % p;
		invfact[i] = (lli)inv[i] * invfact[i-1] % p;
	}
	int t;
	cin >> t;
	while(t--){
		int n, P, r;
		cin >> n >> P >> r;
		vector<int> pol = stirling(r-1);
		int p_pow = P;
		lli ans = 0;
		bool alt = !(r & 1);
		for(lli pi : pol){
			if(alt) pi = (p - pi) % p;
			if(p_pow == 1){
				(ans += pi * (n+1)) %= p;
			}else{
				int pn = powerMod(p_pow, n+1);
				(ans += pi * (pn - 1) % p * powerMod(p_pow - 1, -1)) %= p;
			}
			p_pow = (lli)p_pow * P % p;
			alt = !alt;
		}
		ans = ans * powerMod(fact[r], -1) % p;
		cout << ans << "\n";
	}
	return 0;
}