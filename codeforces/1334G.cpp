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

const int p = 81788929, g = 7;
const int w = powerMod(g, (p-1)/26, p);

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	vector<int> pi(256);
	for(int i = 0; i < 26; ++i){
		int p;
		cin >> p;
		pi[i + 'a'] = p-1 + 'a';
	}
	string s, t;
	cin >> s >> t;
	reverse(s.begin(), s.end());
	string u = s;
	for(char & c : u){
		c = pi[c];
	}
	vector<bool> res(t.size() - s.size() + 1);
	vector<int> S(s.size()), U(s.size()), V(s.size()), T(t.size()), T2(t.size());
	for(int i = 0; i < s.size(); ++i){
		S[i] = powerMod(w, s[i]-'a', p);
		U[i] = powerMod(w, u[i]-'a', p);
		V[i] = powerMod(w, (s[i]-'a') + (u[i]-'a'), p);
	}
	for(int i = 0; i < t.size(); ++i){
		T[i] = powerMod(w, -(t[i]-'a'), p);
		T2[i] = (lli)T[i] * T[i] % p;
	}
	auto Ra = convolution<p, g>(S, T);
	auto Rb = convolution<p, g>(U, T);
	auto Rab = convolution<p, g>(V, T2);
	for(int j = 0; j <= t.size() - s.size(); ++j){
		int pos = j+s.size()-1;
		int r = (Ra[pos] + Rb[pos] - Rab[pos]) % p;
		if(r < 0) r += p;
		res[j] = res[j] | (r == s.size());
	}
	for(bool val : res) cout << val;
	cout << "\n";
	return 0;
}